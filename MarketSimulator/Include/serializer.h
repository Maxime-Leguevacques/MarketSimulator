// This class is used to handle serialization of bars and not as a storage point to be used by the project in runtime,
// as well as other needed data serialization.


#pragma once

#include <filesystem>

#include "Finance/Common/bars.h"


class Serializer
{
private:
    Serializer() = delete;

private:
    static void CreateDatabase(const std::filesystem::path& _path);
    static void SaveBar(const std::filesystem::path& _path, const Bar& _bar);
};
