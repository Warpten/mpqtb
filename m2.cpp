#include "m2.hpp"

#include <cassert>

namespace fs {
    m2::m2(uint8_t const* fileData) : _fileData(fileData) {
        memcpy(&_header, fileData, sizeof(_header));
        _cursor = sizeof(_header);

        assert(_header.magic == '02DM' && "Non-handled M2 version");
    }
}