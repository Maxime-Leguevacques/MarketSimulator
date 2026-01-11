#pragma once

#include <filesystem>

#include "Common/bars.h"


class Serializer
{
private:
    Serializer() = delete;

private:
    static void CreateDatabase(const std::filesystem::path& _path);
    static void SaveBar(const std::filesystem::path& _path, const Bar& _bar);
};
