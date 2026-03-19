// The 'market' class is used to create the logic of price calculation for upcoming bars. As per the definition: "A
// financial market is the place, physical or virtual, where market actors (buyers and sellers) meat each other to
// discuss financial products".


#pragma once

#include <chrono>

#include "orderBook.h"
#include "matchingEngine.h"


class Market
{
private:
    std::vector<Order> orders_;    
    
    OrderBook* orderBook_ = nullptr;
    MatchingEngine* matchingEngine_ = nullptr;
    
    std::chrono::steady_clock::time_point lastUpdate_;
    float timeTickAccumulator_ = 0.0f;
    float orderTickAccumulator_ = 0.0f;

    std::time_t startEpoch_;
    unsigned int seconds_;
    unsigned int ocount_ = 0;    // Temporary variable to store order index
    
public:
    bool isPlaying = false;
    float timeTick = 1.0f;    // the flow of time in the simulation
    float orderTick = 10.0f;        // the rate of update of a new order in the market
    int assetStartingPriceCts = 500;
    unsigned int baseStartingQuantity = 1;
    
public:
    Market();
    ~Market();

private:
    
    Order CreateNewOrder();

public:
    void Update();

    // DoTimeTick corresponds to the market time flow update ONLY
    void DoTimeTick();
    // DoOrderTick corresponds to the market simulated tick for a new order to happen and NOT SIMULATED TIME FLOW. 
    void DoOrderTick();
    
    OrderBook* GetOrderBook() const;
    std::vector<Order> GetOrders() const;
};
