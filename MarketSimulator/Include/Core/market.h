// The 'market' class is used to create the logic of price calculation for upcoming bars. As per the definition: "A
// financial market is the place, physical or virtual, where market actors (buyers and sellers) meat each other to
// discuss financial products".


#pragma once

#include <chrono>
#include <vector>

#include "Common/bars.h"


class Market
{
private:
    std::chrono::steady_clock::time_point lastUpdate_;
    float timeAccumulator_ = 0.0f;

    uint32_t idx_ = 1767225600;
    
public:
    float tickSpeed = 1.0f;    // Bars per second

    std::vector<Bar> bars;
    
public:
    Market();
    ~Market();

public:
    void Update();
};
