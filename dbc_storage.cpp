#include "dbc_storage.hpp"
#include "dbc_meta.hpp"
#include "dbc_structures.hpp"

#include "fs_mpq.hpp"

#include <cassert>
#include <stdexcept>

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
        _storage.reserve(_header.RecordCount);

        // sparse tables can be loaded just like non-sparse if they don't have strings
        for (uint32_t i = 0; i < _header.RecordCount; ++i)
        {
            uint32_t index = *reinterpret_cast<const uint32_t*>(recordData);
            LoadRecord(&_storage[index], recordData);
            recordData += meta_t::record_size;
        }
    }

    template <typename T>
    void Storage<T>::FixStringOffsets(T* record, uintptr_t oldBase, uintptr_t newBase)
    {
        uint8_t* rawData = reinterpret_cast<uint8_t*>(record);

        for (uint32_t i = 0; i < meta_t::field_count; ++i)
        {
            if (meta_t::field_types[i] == 's')
            {
                // String offsets are serialized as 4 bytes (x86 pointer size)
                uint32_t arraySize = meta_t::field_sizes[i] / 4;

                for (size_t itr = 0; itr < arraySize; ++itr)
                {
                    uintptr_t currentValue = *reinterpret_cast<uintptr_t*>(rawData);
                    currentValue = currentValue - oldBase + newBase;
                    *reinterpret_cast<uintptr_t*>(rawData) = currentValue;

                    rawData += sizeof(uintptr_t);
                }
            }
            else // field_sizes includes array size (it's sizeof(T[N]))
                rawData += meta_t::field_sizes[i];
        }
    }

    template <typename T>
    void Storage<T>::LoadRecord(T* record, uint8_t const* inputData)
    {
        uint8_t* outputData = reinterpret_cast<uint8_t*>(record);
        for (uint32_t i = 0; i < meta_t::field_count; ++i)
        {
#if !defined(_WIN64) && !defined(__x86_64__ ) && !defined(__ppc64__)
            memcpy(outputData, inputData, sizeof(T));
            FixStringOffsets(record, 0, reinterpret_cast<uintptr_t>(&_stringTable[0]));
#else
            uint32_t arraySize = meta_t::field_sizes[i];
            uint32_t memberDiskSize = arraySize;
            switch (meta_t::field_types[i])
            {
                case 'b':
                    throw std::runtime_error("Not supported");
                    break;
                case 'l':
                    memberDiskSize = 8u;
                    break;
                case 's':
                case 'i':
                case 'n':
                case 'u':
                case 'f':
                    memberDiskSize = 4;
                    break;
            }

            arraySize /= memberDiskSize;

            if (meta_t::field_types[i] == 's')
            {
                for (uint32_t itr = 0; itr < arraySize; ++itr)
                {
                    // x64 pointers span 8 bytes, so there's a bit (hah hah) of hoop jumping
                    size_t stringOffset = *reinterpret_cast<const uint32_t*>(inputData);
                    stringOffset += reinterpret_cast<uintptr_t>(&_stringTable[0]);

                    *reinterpret_cast<uintptr_t*>(outputData) = stringOffset;

                    // Advance pointers
                    outputData += sizeof(uintptr_t);
                    inputData += sizeof(uint32_t);
                }
            }
            else
            {
                memcpy(outputData, inputData, meta_t::field_sizes[i]);
                outputData += meta_t::field_sizes[i];
                inputData += meta_t::field_sizes[i];
            }
#endif
        }
    }

    template struct Storage<MapEntry>;
    template struct Storage<ItemSparseEntry>;
    template struct Storage<SpellEntry>;
    template struct Storage<ChrClassesEntry>;
    template struct Storage<ChrRacesEntry>;
    template struct Storage<CreatureModelDataEntry>;
    template struct Storage<CreatureDisplayInfoEntry>;
    template struct Storage<VehicleSeatEntry>;
}
