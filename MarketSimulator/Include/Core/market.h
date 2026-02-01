// The 'market' class is used to create the logic of price calculation for upcoming bars. As per the definition: "A
// financial market is the place, physical or virtual, where market actors (buyers and sellers) meat each other to
// discuss financial products".


#pragma once

#include <chrono>

#include "chart.h"
#include "orderBook.h"


class Market
{
private:
    OrderBook* orderBook_ = nullptr;
    Chart* chart_ = nullptr;
    
    
    std::chrono::steady_clock::time_point lastUpdate_;
    float timeAccumulator_ = 0.0f;
    
public:
    float tickSpeed = 2.0f;    // Bars per second
    
public:
    Market();
    ~Market();

public:
    void Update();

    OrderBook* GetOrderBook() const;
    Chart* GetChart() const;
};
