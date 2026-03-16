#include "Core/matchingEngine.h"


void MatchingEngine::MatchBuy(OrderBook* _orderBook, Order& _incoming)
{
    if (_orderBook->sells_.empty())
        return;

    const auto it = _orderBook->sells_.begin();
    // First, we need to check if the incoming order has an opposite order on the same price level or lower
    if (_incoming.priceCts < it->first)
        return;

    // Loop until quantity is gone on one side
    std::queue<SMatchableOrder>& queue = it->second;
    while (!queue.empty() && _incoming.qty > 0)
    {
        // Then we take the smallest available sell price
        SMatchableOrder& sell = it->second.front();
        
        // Find the traded quantity
        const unsigned int tradedQty = std::min(_incoming.qty, sell.qty);

        // Reduce quantities
        _incoming.qty -= tradedQty;
        sell.qty -= tradedQty;

        // Erase sell if needed
        if (sell.qty == 0)
            queue.pop();
    }

    // Erase sell price level if empty
    if (queue.empty())
        _orderBook->sells_.erase(it);
    
}

void MatchingEngine::MatchSell(OrderBook* _orderBook, Order& _incoming)
{
    if (_orderBook->buys_.empty())
        return;

    const auto it = _orderBook->buys_.begin();
    // First, we need to check if the incoming order has an opposite order on the same price level or lower
    if (_incoming.priceCts > it->first)
        return;

    // Loop until quantity is gone on one side
    std::queue<SMatchableOrder>& queue = it->second;
    while (!queue.empty() && _incoming.qty > 0)
    {
        // Then we take the smallest available sell price
        SMatchableOrder& buy = it->second.front();

        // Find the traded quantity
        const unsigned int tradedQty = std::min(_incoming.qty, buy.qty);

        // Reduce quantities
        _incoming.qty -= tradedQty;
        buy.qty -= tradedQty;

        // Erase buy if needed
        if (buy.qty == 0)
            queue.pop();
    }

    // Erase buy price level if empty
    if (queue.empty())
        _orderBook->buys_.erase(it);
    
}

void MatchingEngine::FindMatch(OrderBook* _orderBook, Order& _order)
{
    // The following description will describe how to match a buy. It applies by definition in reverse to match a sell.
    //
    //
    // The first step to match a buy is to check if the incoming buy order is on a price level where equal or smaller
    // sells exists.
    //
    // The second step of the matching engines is to find the best possible ask price. This is legally required to
    // "ensure fairness and transparency in the market". This means that a buyer will favor the smallest price available
    // for him
    //
    // The final step concerns the quantity of the incoming order. At this point, we are sure that the incoming buy is
    // trading with asks with the correct price. However, its quantity may differ by being smaller or larger than the
    // ask. We need to match the incoming order until one side has no quantity left. In this process, the ask may run
    // out or not. If not, we keep it, and if it does, we match the remaining quantity of the buy with the next ask in
    // the queue.
    
    _order.direction == EDirection::buy ? MatchBuy(_orderBook, _order) : MatchSell(_orderBook, _order);
}
