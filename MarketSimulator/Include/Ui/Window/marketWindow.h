#pragma once

#include "Ui/window.h"


class MarketWindow : public Window
{
private:
    std::vector<double> dates;
    
public:
    explicit MarketWindow(const std::string& _name);
    virtual ~MarketWindow();

public:
    void Update(Market* _market) override;
};