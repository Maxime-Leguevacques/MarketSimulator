#pragma once

#include "Ui/window.h"


class ChartWindow : public Window
{
public:
    ChartWindow(const std::string& _name);
    ~ChartWindow();

public:
    void Update() override;
};