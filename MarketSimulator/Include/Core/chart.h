#pragma once

#include <vector>

#include "Common/bars.h"


class Chart
{
private:
    std::vector<Bar> bars_;

    uint32_t idx_ = 1767225600;

public:
    Chart();
    ~Chart();

public:
    void Update();

    friend class ChartWindow;
};
