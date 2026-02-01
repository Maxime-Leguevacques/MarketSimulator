#pragma once

#include <string>

#include "Core/market.h"


class Window
{
protected:
    ~Window() = default;

public:
    std::string name;

public:
    explicit Window(std::string _name);
    virtual void Update() = 0;
};
