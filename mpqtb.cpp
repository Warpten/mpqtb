#include "fs_mpq.hpp"
#include "dbc_storage.hpp"

#include <vector>
#include <stdexcept>
#include <string_view>

std::string_view get_argument(std::vector<const char*> const& args, std::string_view key) {
    auto end = (++args.rbegin()).base();
    for (auto itr = args.begin(); itr != end; ++itr)
        if (key == *itr)
            return *(++itr);

    throw std::runtime_error("Argument not found");
}

template <typename T>
std::unique_ptr<datastores::Storage<T>> open_from_mpq(fs::mpq::mpq_file_system const& fs) {
    using meta_t = typename datastores::meta_type<T>::type;

    auto handle = fs.OpenFile(meta_t::name());
    return std::make_unique<datastores::Storage<T>>(handle);
}

int main(int argc, char* argv[]) {
    // Exclude binary path
    std::vector<const char*> arguments(argv + 1, argv + argc);

    auto installPath = get_argument(arguments, "--installPath");
    fs::mpq::mpq_file_system fs(installPath);

    auto creatureDisplayInfo = open_from_mpq<datastores::CreatureDisplayInfoEntry>(fs);
    if (!creatureDisplayInfo)
        throw std::runtime_error("Failed to open CreatureDisplayInfo");

    auto creatureModelData = open_from_mpq<datastores::CreatureModelDataEntry>(fs);
    if (!creatureModelData)
        throw std::runtime_error("Failed to open CreatureModelData");

    // Blah

    return 0;
}