#pragma once

#include <cstdint>
#include <string>
#include <type_traits>
#include <unordered_map>

#include "dbc_traits.hpp"

namespace datastores
{
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

    template <typename T, typename Impl>
    struct iterator_impl {
        using difference_type = typename Impl::difference_type;
        using value_type = T;
        using pointer = std::add_pointer_t<value_type>;
        using reference = std::add_lvalue_reference_t<value_type>;
        using iterator_category = typename Impl::iterator_category;

        /* implicit */ iterator_impl(Impl itr) : _itr(itr), _current(itr->second) { }

        inline pointer operator -> () const { return &_current; }

        inline reference operator * () const {
            return _current;
        }

        iterator_impl<T, Impl>& operator ++ () {
            ++_itr;
            _current = _itr->second;
            return *this;
        }

        friend bool operator == (typename iterator_impl<T, Impl> const& r, typename iterator_impl<T, Impl> const& l) {
            return l._itr == r._itr;
        }

        friend bool operator != (typename iterator_impl<T, Impl> const& r, typename iterator_impl<T, Impl> const& l) {
            return !(l._itr == r._itr);
        }

    private:
        Impl _itr;
        typename Impl::value_type::second_type _current;
    };

    template <typename T>
    struct Storage final
    {
        // This is enough for most use cases - add more as needed
        using value_type      = T;
        using size_type       = typename std::vector<T>::size_type;
        using difference_type = typename std::vector<T>::difference_type;
        using reference       = typename std::vector<T>::reference;
        using const_reference = typename std::vector<T>::const_reference;
        using pointer         = typename std::vector<T>::pointer;
        using const_pointer   = typename std::vector<T>::const_pointer;
        // using iterator =
        // using const_iterator =
        // Defined below

        using meta_t = typename meta_type<T>::type;
        static_assert(!std::is_same<meta_t, std::nullptr_t>::value, "Metadata not found");

        using header_type = typename std::conditional<meta_t::sparse_storage, DB2Header, DBCHeader>::type;
        using record_type = T;

        Storage(uint8_t const* fileData);

    private:
        void CopyToMemory(uint32_t index, uint8_t const* data);

    public:
        T const& operator [] (size_t id) const { return _storage[id]; }

        using iterator = iterator_impl<T, typename std::unordered_map<uint32_t, T>::iterator>;
        using const_iterator = iterator_impl<const T, typename std::unordered_map<uint32_t, T>::const_iterator>;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        // Only const interface exposed
        // iterator begin() noexcept { return iterator(_storage.begin()); }
        // iterator end() noexcept { return iterator(_storage.end()); }

        const_iterator begin() const noexcept { return const_iterator(_storage.begin()); }
        const_iterator end() const noexcept { return const_iterator(_storage.end()); }

        // Only const interface exposed
        // reverse_iterator rbegin() noexcept { return reverse_iterator(begin()); }
        // reverse_iterator rend() noexcept { return reverse_iterator(end()); }

        const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(begin()); }
        const_reverse_iterator rend() const noexcept { return const_reverse_iterator(end()); }

    private:
        header_type _header;
        std::unordered_map<uint32_t, T> _storage;
        std::vector<uint8_t> _stringTable;
    };

    

}
