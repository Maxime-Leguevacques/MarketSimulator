#include "Core/market.h"

#include <iostream>
#include <random>

#include "Core/Common/order.h"


int seconds = 0;

Market::Market()
{
    lastUpdate_ = std::chrono::steady_clock::now();

    orderBook_ = new OrderBook();
}

Market::~Market() = default;

void Market::DoOrderTick()
{
    const Order order = CreateNewOrder();
    orders_.push_back(order);
    // Add to order book
    orderBook_->AddOrder(order);
    // Increment order index
    ocount_++;
}

void Market::DoTimeTick()
{
    seconds++;
    std::cout << seconds << std::endl;
}

Order Market::CreateNewOrder()
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

OrderBook* Market::GetOrderBook() const
{
    return orderBook_;
}

std::vector<Order> Market::GetOrders() const
{
    return orders_;
}
