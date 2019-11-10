#include "m2.hpp"

#include <cassert>

namespace fs {
    m2::m2(uint8_t const* fileData, size_t fileSize) {
        _fileData.resize(fileSize);
        memcpy(_fileData.data(), fileData, fileSize);

        assert(header()->magic == '02DM' && "Non-handled M2 version");
    }

    m2::header_t const* m2::header() const {
        return reinterpret_cast<const header_t*>(_fileData.data());
    }
}