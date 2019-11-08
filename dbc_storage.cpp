#include "dbc_storage.hpp"
#include "dbc_meta.hpp"
#include "dbc_structures.hpp"

#include "fs_mpq.hpp"

#include <cassert>

// Fucking windows.
#ifdef max
#undef max
#endif

namespace datastores
{
    template <typename T>
    Storage<T>::Storage(uint8_t const* fileData)
    {
        if (fileData == nullptr)
            return;

        _storage.clear();
        memcpy(&_header, fileData, sizeof(header_type));

        if (!meta_t::sparse_storage)
            assert(_header.Magic == 'CBDW');
        else
            assert(_header.Magic == '2BDW');

        uint8_t const* recordData = fileData + sizeof(header_type);
        if constexpr (meta_t::sparse_storage)
            recordData += (4uL + 2uL) * ((size_t) _header.MaxIndex - (size_t)_header.MinIndex + 1uL);
        uint8_t const* stringTableData = recordData + (size_t) _header.RecordCount * (size_t) _header.RecordSize;

        _stringTable.assign(stringTableData, stringTableData + _header.StringBlockSize);

        // sparse tables can be loaded just like non-sparse if they don't have strings
        for (uint32_t i = 0; i < _header.RecordCount; ++i)
            CopyToMemory(i, fileData + (size_t)i * (size_t)meta_t::record_size);
    }

    template <typename T>
    void Storage<T>::CopyToMemory(uint32_t index, uint8_t const* data)
    {
        static_assert(alignof(T) == 1, "Structures passed to Storage<T, ...> must be aligned to 1 byte. Use #pragma pack(push, 1)!");

        uint32_t memoryOffset = 0;
        uint8_t* structure_ptr = reinterpret_cast<uint8_t*>(&_storage[*reinterpret_cast<uint32_t const*>(data)]); // fixme find indexof n
        for (uint32_t j = 0; j < meta_t::field_count; ++j)
        {
            uint8_t* memberTarget = structure_ptr + memoryOffset;
            assert(reinterpret_cast<uintptr_t>(memberTarget) < reinterpret_cast<uintptr_t>(structure_ptr + sizeof(T)));

            auto array_size = meta_t::field_sizes[j];
            auto memory_size_item = 4u;
            switch (meta_t::field_types[j])
            {
            case 's':
            case 'i':
            case 'n':
            case 'u':
            case 'f':
                break;
            case 'l':
                memory_size_item = 8u;
                break;
            case 'b':
                memory_size_item = 1u;
                break;
            }

            array_size /= memory_size_item;

            if (meta_t::field_types[j] == 's')
            {
                for (uint32_t i = 0; i < array_size; ++i)
                {
                    if constexpr (true) // (!meta_t::sparse_storage) // WDB2 still has a string table
                    {
                        auto stringTableOffset = *reinterpret_cast<uint32_t const*>(data + meta_t::field_offsets[j] + 4u * i);
                        const char* stringValue = reinterpret_cast<const char*>(&_stringTable[stringTableOffset]);
                        *reinterpret_cast<uintptr_t*>(memberTarget) = reinterpret_cast<uintptr_t>(stringValue);
                    }
                    else
                    {
                        uint8_t const* recordMember = data + meta_t::field_offsets[j] + 4u * i;
                        size_t stringLength = strlen(reinterpret_cast<const char*>(recordMember));
                        auto itr = &*_stringTable.insert(_stringTable.end(), recordMember, recordMember + stringLength);
                        *reinterpret_cast<uintptr_t*>(memberTarget) = *reinterpret_cast<uintptr_t*>(*itr);
                    }

                    memoryOffset += sizeof(uintptr_t); // // Advance to the next member ...
                    memberTarget += sizeof(uintptr_t); // ... But also advance our own pointer in case we are an array.
                }
            }
            else
            {
                if (memory_size_item > meta_t::field_sizes[j])
                {
                    for (size_t i = 0; i < array_size; ++i)
                    {
                        memcpy(memberTarget, data + meta_t::field_offsets[j] + i * memory_size_item, memory_size_item);
                        constexpr static const uint32_t masks[] = { 0x000000FFu, 0x0000FFFFu, 0x00FFFFFFu, 0xFFFFFFFFu };
                        *reinterpret_cast<uint32_t*>(memberTarget) &= masks[meta_t::field_sizes[j] - 1];

                        memoryOffset += memory_size_item;
                        memberTarget += memory_size_item;
                    }
                }
                else
                {
                    memcpy(memberTarget, data + meta_t::field_offsets[j], meta_t::field_sizes[j]);
                    memoryOffset += meta_t::field_sizes[j];
                }
            }
        }
    }

    template struct Storage<MapEntry>;
    template struct Storage<ItemSparseEntry>;
    template struct Storage<SpellEntry>;
    template struct Storage<ChrClassesEntry>;
    template struct Storage<ChrRacesEntry>;
    template struct Storage<CreatureModelDataEntry>;
    template struct Storage<CreatureDisplayInfoEntry>;
}
