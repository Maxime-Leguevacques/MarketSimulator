#pragma once

#include <vector>

#include "Common/bars.h"
#include "Common/order.h"


class Chart
{
    friend class ChartWindow;
    
private:
    std::vector<Bar> bars_;

    uint32_t idx_ = 1767225600;

public:
    Chart();
    ~Chart();

public:
    void Update();
    void AddOrder(const Order& _order);
};
