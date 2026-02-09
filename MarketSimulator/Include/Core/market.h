// The 'market' class is used to create the logic of price calculation for upcoming bars. As per the definition: "A
// financial market is the place, physical or virtual, where market actors (buyers and sellers) meat each other to
// discuss financial products".


#pragma once

#include <chrono>

#include "orderBook.h"
#include "matchingEngine.h"
#include "chart.h"


class Market
{
private:
    OrderBook* orderBook_ = nullptr;
    MatchingEngine* matchingEngine_ = nullptr;
    Chart* chart_ = nullptr;
    
    std::chrono::steady_clock::time_point lastUpdate_;
    float timeAccumulator_ = 0.0f;

    unsigned int ocount_ = 0;    // Temporary variable to store order index
    
public:
    bool isPlaying = false;
    float tickSpeed = 1.0f;    // Bars per second
    int assetStartingPriceCts = 500;
    unsigned int baseStartingQuantity = 1;
    
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
