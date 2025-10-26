#pragma once

#include <string>


class Window
{
public:
    std::string name;

public:
    Window(const std::string& _name) : name(_name) {}
    virtual void Update() = 0;
};
