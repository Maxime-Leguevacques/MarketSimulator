#include "serializer.h"

#include <iostream>

#include "Common/utils.h"
#include "SQLite/sqlite3.h"


void Serializer::CreateDatabase(const std::filesystem::path& _path)
{
    sqlite3* db;

    if (sqlite3_open(_path.string().c_str(), &db) != SQLITE_OK)
        std::cerr << Utils::messageTypeError << "Error opening database: " << sqlite3_errmsg(db) << std::endl;

    const char* createTableSQL =
        "CREATE TABLE IF NOT EXISTS Bars ("
        "t INTEGER, "
        "tc INTEGER, "
        "o REAL, "
        "h REAL, "
        "l REAL, "
        "c REAL, "
        "v REAL, "
        "n INTEGER);";

    char* errMsg = nullptr;
    if (sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        std::cerr << "Error creating table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void Serializer::SaveBar(const std::filesystem::path& _path, const Bar& _bar)
{
    // sqlite3* db;
    
}
