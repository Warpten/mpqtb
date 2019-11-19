#include "mysql.hpp"

#include <stdexcept>

namespace db {
    mysql::mysql(std::string_view host, uint32_t port, std::string_view user, std::string_view pw, std::string_view db) {
        _conn = mysql_init(nullptr);
        if (!mysql_real_connect(_conn, host.data(), user.data(), pw.data(), db.data(), port, nullptr, 0))
            throw std::runtime_error("db connection failed");
    }

    mysql::~mysql() {
        mysql_close(_conn);
    }

    result_set mysql::select(std::string_view query) {
        if (mysql_query(_conn, query.data()))
            throw std::runtime_error("query failed");

        return result_set{ mysql_use_result(_conn) };
    }
}