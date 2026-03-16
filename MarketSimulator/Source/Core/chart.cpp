#include <algorithm>

#include "Core/chart.h"


Chart::Chart(Market* _market)
    : market_(_market)
{}

Chart::~Chart() = default;

void Chart::MakeBars(const std::vector<Order>& _orders, const EInterval _interval)
{
    bars_.clear();
    if (_orders.empty())
        return;

    const int intervalSec = IntervalToSeconds(_interval);
    
    size_t startIdx = 0;
    while (startIdx < _orders.size())
    {
        // Get open time
        const std::time_t openTime = _orders[startIdx].epoch;
        // Compute close time depending on interval
        const std::time_t closeTime = openTime + intervalSec;
        // Get open price
        const unsigned int openPrice = _orders[startIdx].priceCts;
    
        // Prepare variables
        unsigned int highPrice = openPrice;
        unsigned int lowPrice = openPrice;
        unsigned int closePrice = openPrice;
        float volume = 0.0f;
        int numberOfTrades = 0;
        
        size_t i = startIdx;
        while (i < _orders.size() && _orders[i].epoch < closeTime)
        {
            const Order& order = _orders[i];
            // Get high price
            highPrice = std::max<unsigned int>(order.priceCts, highPrice);
            // Get low price
            lowPrice = std::min<unsigned int>(order.priceCts, lowPrice);
            // Get close price
            closePrice = order.priceCts;
            // Get volume
            volume += static_cast<float>(order.qty);
            numberOfTrades++;
            i++;
        }
        
        bars_.push_back({
            static_cast<uint32_t>(openTime),
            static_cast<uint32_t>(closeTime),
            static_cast<float>(openPrice),
            static_cast<float>(highPrice),
            static_cast<float>(lowPrice),
            static_cast<float>(closePrice),
            volume,
            numberOfTrades
        });
        
        // Update start index
        startIdx = i;
    }
}

int Chart::IntervalToSeconds(const EInterval _interval) const
{
    switch (_interval)
    {
    case second: return 1;
    case minute: return 60;
    case hour:   return 60 * 60;
    case day:    return 24 * 60 * 60;
    }
    return 60;
}

void Chart::Update()
{
    MakeBars(market_->GetOrders(), interval);
    prevSelectedInterval_ = selectedInterval_;
}
