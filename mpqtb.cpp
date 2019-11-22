#include "fs_mpq.hpp"
#include "dbc_storage.hpp"
#include "m2.hpp"
#include "mysql.hpp"

#include "vectors.hpp"
#include "matrices.hpp"

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


bool hasAttachment(wow::m2 const& model, uint32_t attachmentId) {
    auto attachmentIndicesById = (model << model.header()->attachmentIndicesById);
    auto attachments = (model << model.header()->attachments);

    if (attachmentId < attachmentIndicesById.size())
        return attachmentIndicesById[attachmentId] < attachments.size();

    return attachments.size() > 0xFFFF;
}

std::optional<wow::C3Vector> getAttachmentPivot(wow::m2 const& model, uint32_t attachmentID) {
    auto header = model.header();

    auto attachmentIndice = -1;
    if (attachmentID < header->attachmentIndicesById.count)
        attachmentIndice = (model << header->attachmentIndicesById)[attachmentID];
    else
        return std::nullopt;

    auto attachments = (model << header->attachments);
    if (attachmentIndice > attachments.size())
        return std::nullopt;

    return attachments[attachmentIndice].position;
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

void translate(wow::C44Matrix& m, wow::C4Vector const& v) { // UNVERIFIED
    float v3; // xmm1_4
    float v4; // xmm0_4
    float v5; // xmm1_4

    v3 = m[1].y;
    m[3].x = (((m[2].x * v.z) + (m[1].x * v.y)) + (v.x * m[0].x)) + m[3].x * v.o;
    v4 = (((m[2].y * v.z) + (v3 * v.y)) + (m[0].y * v.x)) + m[3].y * v.o;
    v5 = m[1].z;
    m[3].y = v4;
    m[3].z = (((m[2].z * v.z) + (v5 * v.y)) + (m[0].z * v.x)) + m[3].z * v.o;
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

struct CVehiclePassenger_C
{
    struct matref {
        bool _hasValue;
        wow::C44Matrix _mat;

        matref() : _hasValue(false) { }
        matref(wow::C44Matrix const& m) : _mat(m), _hasValue(true) {
        }

        inline wow::C44Matrix& operator = (wow::C44Matrix const& m) {
            _mat = m;
            return _mat;
        }

        inline wow::C44Matrix const& value() const { return _mat; }
        inline wow::C44Matrix& value() { return _mat; }
        inline operator bool() const { return _hasValue; }
    };

    CVehiclePassenger_C(wow::m2 const& model, datastores::CreatureDisplayInfoEntry const& cde, datastores::CreatureModelDataEntry const& cmd) : model(model), cdi(cde), cmd(cmd) { }

    wow::C44Matrix getAttachmentWorldTransform(int attachmentID) {
        auto attachmentIndices = (model << model.header()->attachmentIndicesById);
        auto attachments = (model << model.header()->attachments);

        int16_t bone = 0;
        int16_t attachmentIndice = -1;
        if (attachmentID >= 0 && attachmentID < attachmentIndices.size()) {
            attachmentIndice = attachmentIndices[attachmentID];
            if (attachmentIndice >= 0 && attachmentIndice < attachments.size())
                bone = attachments[attachmentIndice].bone;
        }

        animate();

        if (attachmentIndice == -1 ) {
            return boneTransformationMatrices[0].value();
        }
        else {
            auto result = getBoneMatrix(bone);
            if (!result)
                throw std::runtime_error("oof");
            ::translate(result.value(), attachments[attachmentIndice].position);
            return result.value();
        }
    }

    void animate() {
        auto boneIndices = (model << model.header()->boneIndicesById);
        auto bones = (model << model.header()->bones);

        for (uint32_t i = 0; i < bones.size(); ++i) {
            calculateBoneMatrix(bones[i], i);
        }
    }

    matref& getBoneMatrix(uint32_t boneIndice) {
        return boneTransformationMatrices[boneIndice];
    }

    wow::C44Matrix calculateBoneMatrix(wow::M2CompBone const& bone, uint32_t boneIndice) {
        if (boneTransformationMatrices[boneIndice])
            return boneTransformationMatrices[boneIndice].value();

        auto bones = (model << model.header()->bones);

        wow::C44Matrix boneMat;
        make_identity(boneMat);

        wow::C44Matrix parentBoneMatrix;
        make_identity(parentBoneMatrix);
        if (bone.parent_bone >= 0) {
            parentBoneMatrix = calculateBoneMatrix(bones[bone.parent_bone], bone.parent_bone);
            wow::C44Matrix modifiedParentBoneMatrix = parentBoneMatrix;

            if (bone.flags & 0x7) {
                if ((bone.flags & 04) && (bone.flags & 0x02)) {

                }
                else if (bone.flags & 0x04) {

                }
                else if (bone.flags & 0x02) {

                }

                if (bone.flags & 0x01) {

                }
                else {
                    auto pivot1 = wow::C4Vector(bone.pivot, 1.0f);
                    auto negPivot0 = wow::C4Vector(bone.pivot.neg(), 0.0f);

                    modifiedParentBoneMatrix[3] = (parentBoneMatrix * pivot1) - (modifiedParentBoneMatrix * negPivot0);
                    modifiedParentBoneMatrix[3].o = 1.0f;
                }

                parentBoneMatrix = modifiedParentBoneMatrix;
            }
        }

        auto pivot = wow::C4Vector(bone.pivot, 0.0f);
        auto negPivot = wow::C4Vector(bone.pivot.neg(), 0.0f);

        bool isAnimated = (bone.flags & 0x280);
        bool isBillboarded = (bone.flags & 0x78);

        if (isAnimated) {
            // calcAnimationTransform - whatever
            wow::C44Matrix animationTransform;
            make_identity(animationTransform);

            boneMat = parentBoneMatrix * animationTransform;
        }
        else {
            boneMat = parentBoneMatrix;
        }

        if (isBillboarded) {
            wow::C3Vector scale(boneMat[0].length(), boneMat[1].length(), boneMat[2].length());
            auto boneMatCopy = boneMat;

            if (bone.flags & 0x10) {
                // y axis billboard
            } else if (bone.flags & 0x20) {
                // x axis billboard
            } else if (bone.flags & 0x40) {
                // another axis billboard
            } else if (bone.flags & 0x08) {
                if (isAnimated) {
                    // billboard everything??
                }
                else {
                    boneMat[0] = wow::C4Vector(0.0f, 0.0f, -1.0f, 0.0f);
                    boneMat[1] = wow::C4Vector(1.0f, 0.0f,  0.0f, 0.0f);
                    boneMat[2] = wow::C4Vector(0.0f, 1.0f,  0.0f, 0.0f);
                }
            }
            wow::C4Vector pivot1(bone.pivot, 1.0f);
            wow::C4Vector pivot0(bone.pivot, 0.0f);

            boneMat[0] *= scale.x;
            boneMat[1] *= scale.y;
            boneMat[2] *= scale.z;
            boneMat[3] = (boneMatCopy * pivot1) - (boneMat * pivot0);
            boneMat[3].o = 0.0f;
        }

        boneTransformationMatrices[boneIndice] = matref(boneMat);
        return boneMat;
    }

    wow::C3Vector computeSeatPosition(datastores::VehicleSeatEntry const& vse) {
        wow::C3Vector seatPosition;

        if (!(m_flags & 0x20))
            onVehicleSeatRecUpdate(vse);

        auto attachmentID = -1;
        if (vse.AttachmentID < 26)
            attachmentID = g_vehicleGeoComponentsLinks[vse.AttachmentID];

        if (m_flags & 0x20 && m_flags & 0x40) {
            wow::C44Matrix modelTransform = computeModelTransform(vse, attachmentID);
            memcpy(&seatPosition, &modelTransform[3], sizeof(wow::C3Vector));
        }
        else {
            seatPosition = vse.AttachmentOffset;
        }

        wow::C44Matrix modelTransform; make_identity(modelTransform);
        if (hasAttachment(model, attachmentID)) {
            wow::C44Matrix modelTransform = getAttachmentWorldTransform(attachmentID);

            { // Translation
                float v18 = (float)((float)((float)(seatPosition.z * modelTransform[2].y)
                    + (float)(seatPosition.y * modelTransform[1].y))
                    + (float)(seatPosition.x * modelTransform[0].y))
                    + modelTransform[3].y;
                float v19 = (float)((float)((float)(seatPosition.z * modelTransform[2].z)
                    + (float)(seatPosition.y * modelTransform[1].z))
                    + (float)(seatPosition.x * modelTransform[0].z))
                    + modelTransform[3].z;
                seatPosition.x = (float)((float)((float)(seatPosition.x * modelTransform[0].x)
                    + (float)(seatPosition.z * modelTransform[2].x))
                    + (float)(seatPosition.y * modelTransform[1].x))
                    + modelTransform[3].x;
                seatPosition.y = v18;
                seatPosition.z = v19;
            }

            sub_57D110(&modelTransform);
            float trueScale = getTrueScale(); // unit->getTrueScale()
            if (modelTransform[2].z <= 1.0f) {
                seatPosition.x -= modelTransform[3].x;
                seatPosition.y -= modelTransform[3].y;
                seatPosition.z -= modelTransform[3].z;
            }
            else {
                throw std::runtime_error("not implemented");
            }

            wow::C44Matrix v42 = buildSmoothMatrix(); // unit->buildSmoothMatrix()
            ::scale(v42, trueScale);

            if (modelTransform[2].z <= 1.0f) {
                seatPosition.x += v42[3].x;
                seatPosition.y += v42[3].y;
                seatPosition.z += v42[3].z;
            }
            else {
                float v30 = seatPosition.x;
                float v31 = (float)((float)((float)(seatPosition.z * v42[2].y)
                    + (float)(seatPosition.y * v42[1].y))
                    + (float)(v30 * v42[0].y))
                    + v42[3].y;
                float v32 = (float)((float)((float)(seatPosition.z * v42[2].z)
                    + (float)(seatPosition.y * v42[1].z))
                    + (float)(v30 * v42[0].z))
                    + v42[3].z;
                seatPosition.x = (float)((float)((float)(v30 * v42[0].x)
                    + (float)(seatPosition.z * v42[2].x))
                    + (float)(seatPosition.y * v42[1].x))
                    + v42[3].x;
                seatPosition.y = v31;
                seatPosition.z = v32;
            }
        }
        else {
            wow::C44Matrix v35; make_identity(v35);
            float v36 = seatPosition.y;
            float v37 = seatPosition.z;
            float v38 = (float)((float)((float)(v35[0].y * seatPosition.x) + (float)(v35[1].y * v36))
                + (float)(v35[2].y * v37))
                + v35[3].y;
            float v39 = (float)((float)((float)(v35[1].x * v36) + (float)(v35[2].x * v37))
                + (float)(seatPosition.x * v35[0].x))
                + v35[3].x;
            seatPosition.z = (float)((float)((float)(v35[0].z * seatPosition.x)
                + (float)(v35[1].z * v36))
                + (float)(v35[2].z * v37))
                + v35[3].z;
            seatPosition.y = v38;
            seatPosition.x = v39;
        }

        return seatPosition;
    }

    void sub_57D110(wow::C44Matrix* modelTransform) {
        animate();
        // operator*(modelTransform, &model->m_positionMatrix, (C44Matrix *)(this->m_scene + 296));
        make_identity(*modelTransform);
    }

    wow::C44Matrix buildSmoothMatrix() {
        // get rotation, scale, translation
        // for us this is identity
        wow::C44Matrix mtx;
        make_identity(mtx);
        return mtx;
    }

    float getTrueScale() {
        return cmd.ModelScale * cdi.ModelScale;
    }

    wow::C44Matrix computeModelTransform(datastores::VehicleSeatEntry const& vse, uint32_t attachmentID) {
        wow::C44Matrix modelTransform;
        make_identity(modelTransform);

        float scale = getTrueScale();
        if (hasAttachment(model, attachmentID)) {
            auto attachmentWorldTransform = getAttachmentWorldTransform(attachmentID);

            scale = attachmentWorldTransform[0].length();
            if (scale > 0.0f)
                scale = getTrueScale() / scale;

            ::scale(attachmentWorldTransform, scale);
            scale = 1.0f;
        }
        else {
            ::scale(modelTransform, scale);
        }

        wow::C3Vector scaledAttchOfs(vse.AttachmentOffset);
        scaledAttchOfs.x *= scale;
        scaledAttchOfs.y *= scale;
        scaledAttchOfs.z *= scale;

        if (this->m_flags & 0x20 && m_flags & 0x40) {
            float v26 = this->negatedPivot.y;
            float v27 = this->negatedPivot.z;
            float v28 = this->negatedPivot.x;
            float v29 = (float)((float)((float)(modelTransform[1].x * v26) + (float)(modelTransform[2].x * v27))
                + (float)(modelTransform[0].x * v28))
                + modelTransform[3].x;
            float v30 = (float)((float)((float)(modelTransform[0].y * v28) + (float)(modelTransform[1].y * v26))
                + (float)(modelTransform[2].y * v27))
                + modelTransform[3].y;
            scaledAttchOfs.z += (float)((float)((float)((float)(modelTransform[0].z * v28)
                + (float)(modelTransform[1].z * v26))
                + (float)(modelTransform[2].z * v27))
                + modelTransform[3].z);
            scaledAttchOfs.x += v29;
            scaledAttchOfs.y += v30;
        }

        modelTransform[3] = wow::C4Vector(scaledAttchOfs, modelTransform[3].o);

        if (!hasAttachment(model, attachmentID)) {
            // not a code path for this isue...
        }

        return modelTransform;
    }

    void onVehicleSeatRecUpdate(datastores::VehicleSeatEntry const& vse) {
        if (hasAttachment(model, vse.Passenger.AttachmentID)) {
            negatedPivot = getAttachmentPivot(model, vse.Passenger.AttachmentID).value();
            negatedPivot.x *= -1.0f;
            negatedPivot.y *= -1.0f;
            negatedPivot.z *= -1.0f;
            m_flags |= 0x40 | 0x20;
        }
        else {
            negatedPivot.x = 0.0f;
            negatedPivot.y = 0.0f;
            negatedPivot.z = 0.0f;
            m_flags = (m_flags & ~0x40) | 0x20;
        }
    }

    uint32_t m_flags;
    wow::m2 const& model;
    datastores::CreatureModelDataEntry const& cmd;
    datastores::CreatureDisplayInfoEntry const& cdi;
    wow::C3Vector negatedPivot;

    std::unordered_map<uint32_t /* boneIndice */, matref> boneTransformationMatrices;
};


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

    db::mysql db("localhost", 3306, "root", "toor", "tc_world");
    auto result = db.select("SELECT `entry`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `VehicleID` FROM `creature_template` WHERE `VehicleID` <> 0 AND `entry`=36619");

    while (result)
    {
        uint32_t entry;
        std::array<uint32_t, 4> modelIDs;
        std::string creatureName;
        uint32_t vehicleID;

        result >> entry >> modelIDs >> creatureName >> vehicleID;

        VehicleEntry const& vehicleEntry = vehicle[vehicleID];
        std::cout << "-- Creature " << entry << " (" << creatureName << ") uses Vehicle #" << vehicleID << std::endl;

        for (auto&& seatID : vehicleEntry.SeatID) {
            if (seatID == 0)
                continue;

            VehicleSeatEntry const& vse = vehicleSeat[seatID];
            for (auto modelID : modelIDs) {
                if (modelID == 0)
                    continue;

                CreatureDisplayInfoEntry const& cdi = creatureDisplayInfo[modelID];
                CreatureModelDataEntry const& cmd = creatureModelData[cdi.ModelID];
                if (cmd.ModelName == nullptr || strlen(cmd.ModelName) == 0)
                    continue;

                std::string modelName = cmd.ModelName;
                std::transform(modelName.begin(), modelName.end(), modelName.begin(), ::toupper);
                replace(modelName, ".MDX", ".M2");
                replace(modelName, ".MDL", ".M2");

                wow::m2 model = open_m2(fs, modelName);
                CVehiclePassenger_C passenger(model, cdi, cmd);
                auto seatPosition = passenger.computeSeatPosition(vse);

                std::cout << "(" << cmd.ID
                    << ", " << vse.ID
                    << ", " << seatPosition.x << ", " << seatPosition.y << ", " << seatPosition.z
                    << "), -- " << modelName
                    << std::endl;
            }
        }

        ++result;
    }

    return 0;
}