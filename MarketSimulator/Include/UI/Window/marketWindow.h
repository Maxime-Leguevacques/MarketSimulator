#pragma once

#include "UI/window.h"


class MarketWindow : public Window
{
private:
    Market* market_ = nullptr;
    
    std::vector<double> dates_;
    
public:
    explicit MarketWindow(const std::string& _name, Market* _market);
    virtual ~MarketWindow();

public:
    void Update() override;
};