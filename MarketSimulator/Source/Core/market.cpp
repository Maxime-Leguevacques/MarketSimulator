#include "Core/market.h"


Market::Market()
{
    lastUpdate_ = std::chrono::steady_clock::now();

    orderBook_ = new OrderBook();
    chart_ = new Chart();
}

Market::~Market() = default;

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
        // // Create new bar
        // const Bar bar = {idx_, 10.0f, 12.0f, 7.0f, 9.0f, 100.0f, 8};
        // bars.push_back(bar);
        // idx_ += 86400;

        orderBook_->Update();
        chart_->Update();

        // Update chart

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
