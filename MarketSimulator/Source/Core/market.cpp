#include "Core/market.h"

#include <iostream>

#include "Core/Common/order.h"


Market::Market()
{
    lastUpdate_ = std::chrono::steady_clock::now();

    orderBook_ = new OrderBook();
    chart_ = new Chart();
}

Market::~Market() = default;

void Market::TEMP_CreateNewOrder()
{
    Order order(ocount_);
    order.SetPrice(assetStartingPrice);

    // Add to order book
    orderBook_->AddOrder(order);

    ocount_++;
}

void Market::Update()
{
    // Update timer to make market grow with tickSpeed
    const std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    const std::chrono::duration<float> delta = now - lastUpdate_;
    lastUpdate_ = now;
    timeAccumulator_ += delta.count();
    const float secondsPerBar = 1.0f / tickSpeed;

    while (timeAccumulator_ >= secondsPerBar)
    {
        TEMP_CreateNewOrder();
        orderBook_->Update();
        chart_->Update();

        timeAccumulator_ -= secondsPerBar;
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
