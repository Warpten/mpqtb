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
    for (auto itr = args.begin(); itr != end; ++itr)
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
    return fs::m2(fileHandle->GetData());
}

bool replace(std::string& str, const std::string& from, const std::string& to) {
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

    auto installPath = get_argument(arguments, "--installPath");
    fs::mpq::mpq_file_system fs(installPath);

    auto creatureDisplayInfo = open_dbc<CreatureDisplayInfoEntry>(fs);
    auto creatureModelData = open_dbc<CreatureModelDataEntry>(fs);
    auto vehicleSeat = open_dbc<VehicleSeatEntry>(fs);

    std::set<uint32_t> processedModelIDs;

    std::for_each(vehicleSeat.begin(), vehicleSeat.end(),
    [&processedModelIDs, &fs, &creatureModelData, &creatureDisplayInfo](VehicleSeatEntry const& vse) -> void
    {
        auto attachmentID = g_vehicleGeoComponentsLinks[vse.AttachmentID];
        auto passengerAttachmentID = vse.Passenger.AttachmentID; // Not a typo, this one is directly used

    });

    return 0;
}