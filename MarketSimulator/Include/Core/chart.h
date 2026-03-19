#pragma once

#include <vector>

#include "market.h"
#include "Common/bars.h"'


class Chart
{
    friend class ChartWindow;
    
private:
    Market* market_ = nullptr;
    
private:
    std::vector<Bar> bars_;

    uint32_t idx_ = 1767225600;

public:
    Chart(Market* _market);
    ~Chart();
    
private:
    void MakeBars(const std::vector<Order>& _orders);

public:
    void Update();
};
