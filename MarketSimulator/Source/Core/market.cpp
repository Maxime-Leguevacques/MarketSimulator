#include "Core/market.h"

#include <iostream>
#include <random>

#include "Core/Common/order.h"


Market::Market()
{
    lastUpdate_ = std::chrono::steady_clock::now();
    startEpoch_ = std::time(nullptr);
    orderBook_ = new OrderBook();
}

Market::~Market() = default;

Order Market::CreateNewOrder()
{
    Order order(ocount_, seconds_);

    // Random offset
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution dist(-500, 500);    // +/- 5eur
    int offset = dist(rng);

    // Adapt offset to order direction
    if (order.direction == buy)
        offset *= -1;
    
    order.price = assetPrice + offset;
    order.qty = baseStartingQuantity;

    return order;
}

void Market::UpdateAssetPrice(const int _price)
{
    if (_price > 0)
        assetPrice = _price;
}

void Market::Update()
{
    std::cout << assetPrice << std::endl;
    // Update timer to make market grow with tickSpeed
    const std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    const std::chrono::duration<float> cpuDelta = now - lastUpdate_;
    lastUpdate_ = now;
    
    if (isPlaying)
    {
        timeTickAccumulator_ += cpuDelta.count();
        orderTickAccumulator_ += cpuDelta.count();
        
        const float deltaTime = 1.0f / timeTick;
        const float deltaOrder = 1.0f / orderTick;
        
        // Time tick
        while (timeTickAccumulator_ >= deltaTime)
        {
            DoTimeTick();
            timeTickAccumulator_ -= deltaTime;
        }
        // Order tick
        while (orderTickAccumulator_ >= deltaOrder)
        {
            DoOrderTick();
            orderTickAccumulator_ -= deltaOrder;
        }
    }
}

void Market::DoOrderTick()
{
    const Order order = CreateNewOrder();
    orders_.push_back(order);
    // Add to order book
    UpdateAssetPrice(orderBook_->AddOrder(order));
    // Increment order index
    ocount_++;
}

void Market::DoTimeTick()
{
    seconds_++;
}

OrderBook* Market::GetOrderBook() const
{
    return orderBook_;
}

std::vector<Order> Market::GetOrders() const
{
    return orders_;
}
