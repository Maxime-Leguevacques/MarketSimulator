#include "Core/market.h"

#include <iostream>
#include <random>

#include "Core/Common/order.h"


Market::Market()
{
    lastUpdate_ = std::chrono::steady_clock::now();

    orderBook_ = new OrderBook();
    matchingEngine_ = new MatchingEngine(orderBook_);
    chart_ = new Chart();
}

Market::~Market() = default;

void Market::TEMP_CreateNewOrder()
{
    Order order(ocount_);

    // Random offset
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution dist(-1, 5);
    unsigned int offsetCts = dist(rng);

    // Adapt offset to order direction
    if (order.direction == buyer)
        offsetCts *= -1;
    
    order.priceCts = assetStartingPriceCts + offsetCts;
    order.quantity = baseStartingQuantity;
    // Add to order book
    orderBook_->AddOrder(order);
    // Increment order index
    ocount_++;
}

void Market::Update()
{
    // Update timer to make market grow with tickSpeed
    const std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    const std::chrono::duration<float> delta = now - lastUpdate_;
    lastUpdate_ = now;
    
    if (isPlaying)
    {
        timeAccumulator_ += delta.count();
        const float secondsPerBar = 1.0f / tickSpeed;
        
        while (timeAccumulator_ >= secondsPerBar)
        {
            TEMP_CreateNewOrder();
    
            timeAccumulator_ -= secondsPerBar;
        }
    }
    
    orderBook_->Update();
    matchingEngine_->Update();
    chart_->Update();
}

OrderBook* Market::GetOrderBook() const
{
    return orderBook_;
}

Chart* Market::GetChart() const
{
    return chart_;
}
