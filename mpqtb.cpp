#include "fs_mpq.hpp"
#include "dbc_storage.hpp"
#include "m2.hpp"
#include "mysql.hpp"

#include <vector>
#include <stdexcept>
#include <algorithm>
#include <string_view>
#include <iostream>
#include <set>

std::string_view get_argument(std::vector<const char*> const& args, std::string_view key) {
    auto end = (++args.rbegin()).base();
    for (auto itr = args.begin(); itr != end; itr += 2)
        if (key == *itr)
            return *(++itr);

    throw std::runtime_error("Argument not found");
}

template <typename T>
datastores::Storage<T> open_dbc(fs::mpq::mpq_file_system const& fs) {
    using meta_t = typename datastores::meta_type<T>::type;

    std::string filePath = "DBFilesClient/";
    filePath += meta_t::name();
    auto handle = fs.open_file(filePath);
    return datastores::Storage<T>(handle->GetData());
}

wow::m2 open_m2(fs::mpq::mpq_file_system const& fs, std::string const& fileName) {
    auto fileHandle = fs.open_file(fileName);
    return wow::m2(fileHandle->GetData(), fileHandle->GetFileSize());
}

bool replace(std::string& str, std::string_view from, std::string_view to) {
    size_t start_pos = str.find(from);
    if (start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

constexpr static const uint32_t g_vehicleGeoComponentsLinks[] = {
    0x14, 0x22, 0x13, 0x15, 0x16, 0x11, 0x17, 0x18, 0x19, 0x0F, 0x10, 0x25, 0x26,
    0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x00, 0x2F, 0x30, 0x06, 0x05
};

bool getAttachmentPivot(wow::m2 const& model, uint32_t attachmentID, wow::C3Vector& pPivot) {
    auto header = model.header();

    auto attachmentIndice = -1;
    if (attachmentID < header->attachmentIndicesById.count)
        attachmentIndice = (model << header->attachmentIndicesById)[attachmentID];
    else
        return false;

    auto attachments = (model << header->attachments);
    memcpy(&pPivot, &attachments[attachmentIndice].position, sizeof(wow::C3Vector));
    return true;
}

bool onVehicleSeatRecUpdate(datastores::VehicleSeatEntry const& vse, wow::m2 const& model, wow::C3Vector& pPivot) {
    if (!getAttachmentPivot(model, vse.Passenger.AttachmentID, pPivot)) {
        pPivot.x = 0.0f;
        pPivot.y = 0.0f;
        pPivot.z = 0.0f;

        return false;
    } else {
        pPivot.x *= -1.0f;
        pPivot.y *= -1.0f;
        pPivot.z *= -1.0f;

        return true;
    }
}

void make_identity(wow::C44Matrix& m) {
    m.columns[0].x = 1.0f;       // identity matrix
    m.columns[0].y = 0.0f;
    m.columns[0].z = 0.0f;
    m.columns[0].o = 0.0f;
    m.columns[1].x = 0.0f;
    m.columns[1].y = 1.0f;
    m.columns[1].z = 0.0f;
    m.columns[1].o = 0.0f;
    m.columns[2].x = 0.0f;
    m.columns[2].y = 0.0f;
    m.columns[2].z = 1.0f;
    m.columns[2].o = 0.0f;
    m.columns[3].x = 0.0f;
    m.columns[3].y = 0.0f;
    m.columns[3].z = 0.0f;
    m.columns[3].o = 1.0f;
}

void translate(wow::C44Matrix& m, wow::C3Vector const& v) {
    float v3; // xmm1_4
    float v4; // xmm0_4
    float v5; // xmm1_4

    v3 = m[1].y;
    m[3].x = (((m[2].x * v.z) + (m[1].x * v.y)) + (v.x * m[0].x)) + m[3].x;
    v4 = (((m[2].y * v.z) + (v3 * v.y)) + (m[0].y * v.x)) + m[3].y;
    v5 = m[1].z;
    m[3].y = v4;
    m[3].z = (((m[2].z * v.z) + (v5 * v.y)) + (m[0].z * v.x)) + m[3].z;
}

void scale(wow::C44Matrix& m, float s)
{
    m[0].x = m[0].x * s;
    m[0].y = m[0].y * s;
    m[0].z = m[0].z * s;
    m[1].x = m[1].x * s;
    m[1].y = m[1].y * s;
    m[1].z = m[1].z * s;
    m[2].x = m[2].x * s;
    m[2].y = m[2].y * s;
    m[2].z = m[2].z * s;
}

bool getAttachmentWorldTransform(wow::m2 const& model, wow::C44Matrix& ret, uint32_t attachmentID) {
    // this retrieves the bone's own positioning matrix
    // however this is a function of animation data
    // and it then gets translated by attachment position
    // so we just make an identity matrix and translate it
    make_identity(ret);

    if (attachmentID < 0 || attachmentID >= model.header()->attachmentIndicesById.count)
        return false;

    auto attachmentIndices = (model << model.header()->attachmentIndicesById);
    auto attachments = (model << model.header()->attachments);

    auto idx = attachmentIndices[attachmentID];
    translate(ret, attachments[idx].position);
    return true;
}

float getTrueScale() {
    return 1.0f; // fixme
}

void computeModelTransform(wow::C44Matrix& modelTransform, wow::m2 const& model, datastores::VehicleSeatEntry const& vse, uint32_t attachmentID, float unk) {
    wow::C44Matrix worldTransform;
    bool hasAttachment = getAttachmentWorldTransform(model, worldTransform, attachmentID);

    float attachmentScale = getTrueScale();
    if (hasAttachment) {
        float dist = std::sqrt(worldTransform[0].z * worldTransform[0].z
            + worldTransform[0].y * worldTransform[0].y
            + worldTransform[0].x * worldTransform[0].x);

        attachmentScale = 1.0f;

        float scale = getTrueScale(); // ...
        if (dist > 0.0000f)
            scale /= dist;

        ::scale(worldTransform, scale);
    }
    else {
        ::scale(modelTransform, attachmentScale);
    }

    wow::C3Vector scaledAttachmentOffset = vse.AttachmentOffset;
    scaledAttachmentOffset.x *= attachmentScale;
    scaledAttachmentOffset.y *= attachmentScale;
    scaledAttachmentOffset.z *= attachmentScale;


    wow::C3Vector vehiclePivot;
    bool hasVehiclePivot = onVehicleSeatRecUpdate(vse, model, vehiclePivot);
    if (hasVehiclePivot) {
        float v29 = (((modelTransform[1].x * vehiclePivot.y) + (modelTransform[2].x * vehiclePivot.z))
            + (modelTransform[0].x * vehiclePivot.x))
            + modelTransform[3].x;
        float v30 = (((modelTransform[0].y * vehiclePivot.x) + (modelTransform[1].y * vehiclePivot.y))
            + (modelTransform[2].y * vehiclePivot.z))
            + modelTransform[3].y;
        scaledAttachmentOffset.z = ((((modelTransform[0].z * vehiclePivot.x) + (modelTransform[1].z * vehiclePivot.y))
            + (modelTransform[2].z * vehiclePivot.z))
            + modelTransform[3].z)
            + scaledAttachmentOffset.z;
        scaledAttachmentOffset.x += v29;
        scaledAttachmentOffset.y += v30;
    }

    // Last step applies animation and world position
    // Pray to god we don't need it
    modelTransform[3].x = scaledAttachmentOffset.x;
    modelTransform[3].y = scaledAttachmentOffset.y;
    modelTransform[3].z = scaledAttachmentOffset.z;
}

wow::C3Vector computeSeatPos(wow::m2 const& model, datastores::VehicleSeatEntry const& vse) {
    wow::C3Vector seatPosition;

    wow::C3Vector vehiclePivot;
    bool hasVehiclePivot = onVehicleSeatRecUpdate(vse, model, vehiclePivot);

    auto attachmentID = vse.AttachmentID;
    if (attachmentID > 26) {
        // The game applies the vehicle's placement matrix but for our purpose that's just the identity matrix
        return vse.AttachmentOffset;
    } else {
        attachmentID = g_vehicleGeoComponentsLinks[attachmentID];

        wow::C44Matrix modelTransform;

        if (hasVehiclePivot) {
            make_identity(modelTransform);

            computeModelTransform(modelTransform, model, vse, attachmentID, 0.0f /* ? ? ? */);
            seatPosition.x = modelTransform.columns[3].x;
            seatPosition.y = modelTransform.columns[3].y;
            seatPosition.z = modelTransform.columns[3].z;
        }
        else {
            memcpy(&seatPosition, &vse.AttachmentOffset, sizeof(wow::C3Vector));
        }

        wow::C44Matrix attachmentWorldTransform;
        if (getAttachmentWorldTransform(model, modelTransform, attachmentID)) {
            float v18 = seatPosition.z * attachmentWorldTransform[2].y
                + seatPosition.y * attachmentWorldTransform[1].y
                + seatPosition.x * attachmentWorldTransform[0].y
                + attachmentWorldTransform[3].y;
            float v19 = seatPosition.z * attachmentWorldTransform[2].z
                + seatPosition.y * attachmentWorldTransform[1].z
                + seatPosition.x * attachmentWorldTransform[0].z
                + attachmentWorldTransform[3].z;
            seatPosition.x = seatPosition.z * attachmentWorldTransform[0].x
                + seatPosition.z * attachmentWorldTransform[2].x
                + seatPosition.y * attachmentWorldTransform[1].x
                + attachmentWorldTransform[3].x;
            seatPosition.y = v18;
            seatPosition.z = v19;
        }

        return seatPosition;
    }
}

int main(int argc, char* argv[]) {
    using namespace datastores;

    // Exclude binary path
    std::vector<const char*> arguments(argv + 1, argv + argc);

    auto installPath = get_argument(arguments, "--installPath"); // Path to wow install
    fs::mpq::mpq_file_system fs(installPath);

    auto creatureDisplayInfo = open_dbc<CreatureDisplayInfoEntry>(fs);
    auto creatureModelData = open_dbc<CreatureModelDataEntry>(fs);
    auto vehicleSeat = open_dbc<VehicleSeatEntry>(fs);
    auto vehicle = open_dbc<VehicleEntry>(fs);

    db::mysql db("localhost", 3306, "root", "root", "world");
    auto result = db.select("SELECT `entry`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `VehicleID` FROM `creature_template` WHERE `VehicleID` <> 0");

    while (result) {
        uint32_t entry;
        std::array<uint32_t, 4> modelIDs;
        std::string creatureName;
        uint32_t vehicleID;

        result >> entry >> modelIDs >> creatureName >> vehicleID;

        VehicleEntry const& vehicleEntry = vehicle[vehicleID];
        std::cout << "Creature #" << entry << " (" << creatureName << ") uses Vehicle #" << vehicleID << std::endl;

        ++result;
    }

    return 0;
}