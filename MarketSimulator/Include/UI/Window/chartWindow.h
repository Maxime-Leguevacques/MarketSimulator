#pragma once

#include "UI/window.h"

#include "Core/chart.h"

inline const char* intervalItems[] = { "second", "minute", "hour", "day "};

enum EInterval
{
    second,
    minute,
    hour,
    day
};


class ChartWindow : public Window
{
private:
    Chart* chart_ = nullptr;

    std::vector<double> dates_;

    int selectedInterval_ = 1;

public:
    EInterval interval = EInterval::second;

public:
    explicit ChartWindow(const std::string& _name, Chart* _chart);
    virtual ~ChartWindow();
    
public:
    void Update() override;
    int IntervalToSeconds(const EInterval _interval);
};