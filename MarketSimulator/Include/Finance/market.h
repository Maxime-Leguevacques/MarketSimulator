// The 'market' class is used to create the logic of price calculation for upcoming bars. As per the definition: "A
// financial market is the place, physical or virtual, where market actors (buyers and sellers) meat each other to
// discuss financial products".


#pragma once

#include <vector>

#include "Common/bars.h"


class Market
{
private:
    uint32_t idx = 1767225600;
    
public:
    std::vector<Bar> bars;

    float tickspeed = 1.0f;
    
public:
    Market();
    ~Market();

public:
    void Update();
};
