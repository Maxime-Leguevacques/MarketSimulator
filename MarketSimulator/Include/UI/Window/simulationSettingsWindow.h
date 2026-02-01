#pragma once

#include "UI/window.h"

#include "Core/market.h"


class SimulationSettingsWindow : public Window
{
private:
    Market* market_;
    
public:
    explicit SimulationSettingsWindow(const std::string& _name, Market* _market);
    virtual ~SimulationSettingsWindow();

public:
    void Update() override;
};