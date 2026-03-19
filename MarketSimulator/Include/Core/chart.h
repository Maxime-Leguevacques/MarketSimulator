#pragma once

#include <vector>

#include "market.h"
#include "Common/bars.h"'


inline const char* intervalItems[] = { "second", "minute", "hour", "day "};


enum EInterval
{
    second,
    minute,
    hour,
    day
};


class Chart
{
    friend class ChartWindow;
    
private:
    Market* market_ = nullptr;
    
    int prevSelectedInterval_ = 0;
    int selectedInterval_ = 0;
    
public:
    EInterval interval = EInterval::second;
    
private:
    std::vector<Bar> bars_;

    uint32_t idx_ = 1767225600;

public:
    Chart(Market* _market);
    ~Chart();
    
private:
    void MakeBars(const std::vector<Order>& _orders, EInterval _interval);
    int IntervalToSeconds(const EInterval _interval) const;

public:
    void Update();
};
