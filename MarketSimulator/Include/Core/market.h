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

    unsigned int ocount_ = 0;    // Temporary variable to store order index
    
public:
    float tickSpeed = 1.0f;    // Bars per second
    double assetStartingPrice = 1.0f;
    
public:
    Market();
    ~Market();

private:
    void TEMP_CreateNewOrder();

public:
    void Update();

    OrderBook* GetOrderBook() const;
    Chart* GetChart() const;
};
