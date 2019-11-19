#pragma once

#include <mysql.h>

#include <string_view>
#include <optional>
#include <functional>
#include <vector>

// never ever have i written something as repulsive as this. do not touch
namespace db
{
    struct query;
    struct result_set;

    struct mysql final {
        friend struct query;

        mysql(std::string_view host, uint32_t port, std::string_view user, std::string_view pw, std::string_view db);
        ~mysql();

        result_set select(std::string_view query);

    private:
        MYSQL* _conn;
    };

    struct result_set final {
        result_set(MYSQL_RES* res) : _res(res), _seqIndex(0) {
            auto fieldCount = mysql_num_fields(_res);
            _fields.resize(fieldCount);

            MYSQL_FIELD* fields = mysql_fetch_fields(_res);
            memcpy(_fields.data(), fields, sizeof(MYSQL_FIELD) * fieldCount);

            // Fetch first record
            this->operator++();
        }

        ~result_set() {
            mysql_free_result(_res);
        }

        inline result_set& operator = (MYSQL_ROW r) {
            _row = r;
            return *this;
        }

        inline result_set& operator = (std::nullopt_t nullopt) {
            _row = nullopt;
            return *this;
        }

        inline operator bool() const {
            return _row.has_value();
        }

        inline result_set& operator ++ () {
            _seqIndex = 0;

            auto row = mysql_fetch_row(_res);
            if (row == nullptr)
                _row = std::nullopt;
            else
                _row.value() = row;

            return *this;
        }

        template <typename T, typename Fn = std::function<T(char*)>>
        inline T get(size_t fx, Fn fn) const {
            if (fx >= _fields.size())
                throw std::runtime_error("field index too big");

            if (!_row.has_value())
                throw std::runtime_error("result_set not dereferencable");

            return fn(_row.value()[fx]);
        }

        template <typename T, typename Fn = std::function<T(char*)>>
        inline T get(std::string_view fnm, Fn fn) const {
            size_t index = 0;
            for (auto&& field : _fields) {
                if (fnm == field.name)
                    break;

                ++index;
            }

            return get(index);
        }

        inline result_set& operator >> (std::string& value) {
            value = get<std::string>(_seqIndex++, [](char* v) { return v; });
            return *this;
        }

        inline result_set& operator >> (float& value) {
            value = get<float>(_seqIndex++, [](char* v) { return static_cast<float>(std::atof(v)); });
            return *this;
        }

#define MAKE_ATOI_STREAM_OP(TYPE)                                                                             \
        inline result_set& operator >> (TYPE& value) {                                                        \
            value = get<TYPE>(_seqIndex++, [](char* v) -> TYPE { return static_cast<TYPE>(std::atoi(v)); });  \
            return *this;                                                                                     \
        }

        MAKE_ATOI_STREAM_OP(uint8_t)
        MAKE_ATOI_STREAM_OP(uint16_t)
        MAKE_ATOI_STREAM_OP(uint32_t)
        MAKE_ATOI_STREAM_OP(uint64_t)

        MAKE_ATOI_STREAM_OP(int8_t)
        MAKE_ATOI_STREAM_OP(int16_t)
        MAKE_ATOI_STREAM_OP(int32_t)
        MAKE_ATOI_STREAM_OP(int64_t)
#undef MAKE_ATOI_STREAM_OP

        template <typename T, size_t N>
        inline result_set& operator >> (std::array<T, N>& value) {
            for (int i = 0; i < N; ++i)
                *this >> value[i];
            return *this;
        }

    private:
        MYSQL_RES* _res;
        
        std::optional<MYSQL_ROW> _row;
        std::vector<MYSQL_FIELD> _fields;

        size_t _seqIndex;
    };
}