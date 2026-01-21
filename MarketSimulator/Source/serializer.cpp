#include "serializer.h"

#include <iostream>

#include "Common/utils.h"
#include "SQLite/sqlite3.h"


void Serializer::CreateDatabase(const std::filesystem::path& _path)
{
    sqlite3* db;

    if (sqlite3_open(_path.string().c_str(), &db) != SQLITE_OK)
        std::cerr << Utils::messageTypeError << "Error opening database: " << sqlite3_errmsg(db) << std::endl;

    const char* createTableSql =
        "CREATE TABLE IF NOT EXISTS Bars ("
        "t INTEGER, "
        "o REAL, "
        "h REAL, "
        "l REAL, "
        "c REAL, "
        "v REAL, "
        "n INTEGER);";

    char* errMsg = nullptr;
    if (sqlite3_exec(db, createTableSql, nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        std::cerr << "Error creating table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void Serializer::SaveBar(const std::filesystem::path& _path, const Bar& _bar)
{
    sqlite3* db;

    int rc = sqlite3_open(_path.string().c_str(), &db);
    if (rc != SQLITE_OK)
    {
        std::cerr << Utils::messageTypeError << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_stmt* stmt;

    const char* insertSql =
        "INSERT INTO Bars (t, o, h, l, c, v, n) "
        "VALUES (?, ?, ?, ?, ?, ?, ?);";

    rc = sqlite3_prepare_v2(db, insertSql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        std::cerr << "Prepare failed: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    rc = sqlite3_exec(db, "BEGIN TRANSACTION;", nullptr, nullptr, nullptr);
    if (rc != SQLITE_OK)
    {
        std::cerr << Utils::messageTypeError << "Failed to begin transaction: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }

    // Bind values from the bar
    sqlite3_bind_int64(stmt, 1, _bar.t);
    sqlite3_bind_double(stmt, 2, _bar.o);
    sqlite3_bind_double(stmt, 3, _bar.h);
    sqlite3_bind_double(stmt, 4, _bar.l);
    sqlite3_bind_double(stmt, 5, _bar.c);
    sqlite3_bind_double(stmt, 6, _bar.v);
    sqlite3_bind_int(stmt, 7, _bar.n);

    rc = sqlite3_step(stmt);
    if (rc!= SQLITE_DONE)
        std::cerr << Utils::messageTypeError << "Error inserting new bar: " << sqlite3_errmsg(db) << std::endl;

    sqlite3_reset(stmt);    // Reuse statement
    sqlite3_clear_bindings(stmt);

    rc = sqlite3_exec(db, "END TRANSACTION;", nullptr, nullptr, nullptr);
    if (rc != SQLITE_OK)
        std::cerr << Utils::messageTypeError << "Failed to end transaction: " << sqlite3_errmsg(db) << std::endl;

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
