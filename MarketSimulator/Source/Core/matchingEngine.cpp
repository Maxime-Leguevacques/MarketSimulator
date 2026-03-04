#include "Core/matchingEngine.h"

#include <iostream>


void MatchingEngine::MatchBuy(OrderBook* _orderBook, Order& _incoming)
{
    if (_orderBook->sells_.empty())
        return;

    auto it = _orderBook->sells_.begin();
    // First, we need to check if the incoming order has an opposite order on the same price level or lower
    if (it->first > _incoming.priceCts)
        return;

    // Then we take the smallest available sell price
    SMatchableOrder& sell = it->second.front();
    
    std::cout << "Match from BUY order | BUY: " << _incoming.id << " " << _incoming.qty << " " << _incoming.priceCts;
    std::cout << " -> SELL: " << sell.id << " " << sell.qty << " " << it->first << std::endl;
}

void MatchingEngine::MatchSell(OrderBook* _orderBook, Order& _order)
{
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
    // ask. We need to match the incoming order until it no longer has any quantity left. In this process, the ask
    // may run out or not. If not, we keep it, and if it does, we match the remaining quantity of the buy with the next
    // ask in the queue.
    
    _order.direction == EDirection::buy ? MatchBuy(_orderBook, _order) : MatchSell(_orderBook, _order);
}
