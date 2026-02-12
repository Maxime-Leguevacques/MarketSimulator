// This class includes various useful members and methods useful throughout the project.


#pragma once

#include <string>


struct Vector2
{
    float x;
    float y;
};

struct Vector2Int
{
    int x;
    int y;
};


class Utils
{
public:
    inline static const std::string messageTypeInfo    = "\033[32m[INFO]\033[0m.....";
    inline static const std::string messageTypeStatus  = "[STATUS]...";   
    inline static const std::string messageTypeError   = "\033[31m[ERROR]\033[0m....";
};
