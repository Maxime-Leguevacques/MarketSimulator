#include "Core/market.h"

#include <iostream>
#include <random>

#include "Core/Common/order.h"


Market::Market()
{
    lastUpdate_ = std::chrono::steady_clock::now();

    orderBook_ = new OrderBook();
    chart_ = new Chart();
}

Market::~Market() = default;

void Market::DoTick()
{
}

Order Market::TEMP_CreateNewOrder()
{
    Order order(ocount_);

    // Random offset
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution dist(-1, 5);
    unsigned int offsetCts = dist(rng);

    // Adapt offset to order direction
    if (order.direction == buy)
        offsetCts *= -1;
    
    order.priceCts = assetStartingPriceCts + offsetCts;
    order.qty = baseStartingQuantity;

    return order;
}

void Market::Update()
{
    chart_->Update();
    
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
            Order order = TEMP_CreateNewOrder();
            // Add to order book
            orderBook_->AddOrder(order);
            // Increment order index
            ocount_++;
            
            timeAccumulator_ -= secondsPerBar;
        }
    }
}

OrderBook* Market::GetOrderBook() const
{
    return orderBook_;
}

Chart* Market::GetChart() const
{
    return chart_;
}
