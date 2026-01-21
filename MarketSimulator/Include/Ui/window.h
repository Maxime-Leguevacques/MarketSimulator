#pragma once

#include <string>

#include "Finance/market.h"


class Window
{
protected:
    ~Window() = default;

public:
    std::string name;

public:
    explicit Window(std::string _name) : name(std::move(_name)) {}
    virtual void Update(Market* _market) = 0;
};
