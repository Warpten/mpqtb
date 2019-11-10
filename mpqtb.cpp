#include "fs_mpq.hpp"
#include "dbc_storage.hpp"
#include "m2.hpp"

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
    auto handle = fs.OpenFile(filePath);
    return datastores::Storage<T>(handle->GetData());
}

fs::m2 open_m2(fs::mpq::mpq_file_system const& fs, std::string const& fileName) {
    auto fileHandle = fs.OpenFile(fileName);
    return fs::m2(fileHandle->GetData(), fileHandle->GetFileSize());
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

int main(int argc, char* argv[]) {
    using namespace datastores;

    // Exclude binary path
    std::vector<const char*> arguments(argv + 1, argv + argc);

    auto installPath = get_argument(arguments, "--installPath"); // Path to wow install
    fs::mpq::mpq_file_system fs(installPath);

    auto creatureDisplayInfo = open_dbc<CreatureDisplayInfoEntry>(fs);
    auto creatureModelData = open_dbc<CreatureModelDataEntry>(fs);
    auto vehicleSeat = open_dbc<VehicleSeatEntry>(fs);

    std::for_each(creatureModelData.begin(), creatureModelData.end(),
        [&](CreatureModelDataEntry const& cmde) -> void {
            if (cmde.ModelName == nullptr)
                return;

            // Fix MDX to M2 and uppercase everything
            std::string modelName = cmde.ModelName;
            std::transform(modelName.begin(), modelName.end(), modelName.begin(), ::toupper);
            replace(modelName, ".MDX", ".M2");

            auto modelFile = open_m2(fs, modelName);

            auto header = modelFile.header();

            auto attachments = (modelFile << header->attachments);
            auto boneLookups = (modelFile << header->boneCombos);
            auto bones       = (modelFile << header->bones);

            for (auto&& attachment : attachments)
            {
                if (attachment.bone > header->boneCombos.count)
                    continue;

                auto boneIndex = boneLookups[attachment.bone];
                if (boneIndex > header->bones.count)
                    continue;

                auto&& attachmentPosition = attachment.position;
                auto attachmentDistance = attachmentPosition.length();
                float offsetScale = 0.0f; // GetTrueScale(unit)
                if (attachmentDistance >= 0.0f)
                    offsetScale /= attachmentDistance;

                // Apply model scale to VehicleSeatEntry::AttachmentOffset.
            }
        });

    return 0;
}