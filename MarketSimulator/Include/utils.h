#pragma once

#include <string>
#include <chrono>


class Utils
{
public:
    inline static const std::string messageTypeInfo    = "\033[32m[INFO]\033[0m.....";
    inline static const std::string messageTypeStatus  = "[STATUS]...";   
    inline static const std::string messageTypeError   = "\033[31m[ERROR]\033[0m....";
};
