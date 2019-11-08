#pragma once

#include <cstdint>
#include <string>
#include <type_traits>
#include <unordered_map>

#include "fs_mpq.hpp"
#include "dbc_traits.hpp"

namespace datastores
{
    using namespace fs;

    struct DBCHeader
    {
        uint32_t Magic;
        uint32_t RecordCount;
        uint32_t FieldCount;
        uint32_t RecordSize;
        uint32_t StringBlockSize;
    };

    struct DB2Header
    {
        uint32_t Magic;
        uint32_t RecordCount;
        uint32_t FieldCount;
        uint32_t RecordSize;
        uint32_t StringBlockSize;
        uint32_t TableHash;
        uint32_t Build;
        uint32_t TimestampLastWritten;
        uint32_t MinIndex;
        uint32_t MaxIndex;
        uint32_t Locale;
        uint32_t CopyTableSize;
    };

    template <typename T>
    struct Storage final
    {
        using meta_t = typename meta_type<T>::type;
        static_assert(!std::is_same<meta_t, std::nullptr_t>::value, "");

        using header_type = typename std::conditional<meta_t::sparse_storage, DB2Header, DBCHeader>::type;
        using record_type = T;

        Storage(fs::mpq::mpq_file* fileHandle);

        void LoadRecords(uint8_t const* data);
        void CopyToMemory(uint32_t index, uint8_t const* data);
        T* GetRecord(uint32_t index);

    private:
        header_type& get_header();
        std::unordered_map<uint32_t, T>& get_storage();

        std::vector<uint8_t>& get_string_table();
    };

}
