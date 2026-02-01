#pragma once

#include "UI/window.h"


class ChartWindow : public Window
{
private:
    Chart* chart_ = nullptr;

    std::vector<double> dates_;

public:
    explicit ChartWindow(const std::string& _name, Chart* _chart);
    virtual ~ChartWindow();
    
public:
    void Update() override;
};