#pragma once

#include <mysql.h>

#include <string_view>
#include <optional>
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
    private:
        template <typename T>
        struct transformer { };

        template <>
        struct transformer<std::string> {
            std::string transform(char* value) const {
                return value;
            }
        };

        template <>
        struct transformer<const char*> {
            const char* transform(char* value) const {
                return const_cast<const char*>(value);
            }
        };

        template <>
        struct transformer<uint32_t> {
            uint32_t transform(char* value) const {
                return std::atoi(value);
            }
        };

        template <>
        struct transformer<float> {
            float transform(char* value) const {
                return std::atof(value);
            }
        };

    public:

        result_set(MYSQL_RES* res) : _res(res) {
            auto fieldCount = mysql_num_fields(res);
            _fields.resize(fieldCount);

            MYSQL_FIELD* fields = mysql_fetch_fields(res);
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
            auto row = mysql_fetch_row(_res);
            if (row == nullptr)
                _row = std::nullopt;
            else
                _row.value() = row;

            return *this;
        }

        template <typename T, typename Fn>
        inline T get(size_t fx, Fn fn) const {
            if (fx >= _fields.size())
                throw std::runtime_error("field index too big");

            if (!_row.has_value())
                throw std::runtime_error("result_set not dereferencable");

            return fn(_row.value()[fx]);
        }

        template <typename T, typename Fn>
        inline T get(std::string_view fnm, Fn fn) const {
            size_t index = 0;
            for (auto&& field : _fields) {
                if (fnm == field.name)
                    break;

                ++index;
            }

            return get(index);
        }

    private:
        MYSQL_RES* _res;
        std::optional<MYSQL_ROW> _row;
        std::vector<MYSQL_FIELD> _fields;
    };
}