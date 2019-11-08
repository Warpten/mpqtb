#include "fs_mpq.hpp"
#include "dbc_storage.hpp"

#include <vector>
#include <stdexcept>
#include <algorithm>
#include <string_view>
#include <iostream>

std::string_view get_argument(std::vector<const char*> const& args, std::string_view key) {
    auto end = (++args.rbegin()).base();
    for (auto itr = args.begin(); itr != end; ++itr)
        if (key == *itr)
            return *(++itr);

    throw std::runtime_error("Argument not found");
}

template <typename T>
datastores::Storage<T> open_from_mpq(fs::mpq::mpq_file_system const& fs) {
    using meta_t = typename datastores::meta_type<T>::type;

    auto handle = fs.OpenFile(meta_t::name());
    return datastores::Storage<T>(handle.get());
}

int main(int argc, char* argv[]) {
    using namespace datastores;

    // Exclude binary path
    std::vector<const char*> arguments(argv + 1, argv + argc);

    auto installPath = get_argument(arguments, "--installPath");
    fs::mpq::mpq_file_system fs(installPath);

    auto creatureDisplayInfo = open_from_mpq<CreatureDisplayInfoEntry>(fs);
    auto creatureModelData = open_from_mpq<CreatureModelDataEntry>(fs);

    std::for_each(creatureDisplayInfo.begin(), creatureDisplayInfo.end(), [](datastores::CreatureDisplayInfoEntry const& cde) {
        std::cout << cde.ID;
    });

    return 0;
}