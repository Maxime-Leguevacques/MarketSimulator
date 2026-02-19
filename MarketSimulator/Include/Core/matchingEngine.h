#pragma once

#include "orderBook.h"
#include "Common/order.h"


class MatchingEngine
{
public:
    MatchingEngine() = delete;
    ~MatchingEngine() = delete;

private:
    static void MatchBid(OrderBook* _orderBook, Order& _order);
    static void MatchAsk(OrderBook* _orderBook, Order& _order);
    
public:
    static void FindMatch(OrderBook* _orderBook, Order& _order);
};
