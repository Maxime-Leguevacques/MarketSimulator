#pragma once

#include "orderBook.h"
#include "Common/order.h"


class MatchingEngine
{
public:
    MatchingEngine() = delete;
    ~MatchingEngine() = delete;

private:
    static void MatchBuy(OrderBook* _orderBook, Order& _incoming);
    static void MatchSell(OrderBook* _orderBook, Order& _incoming);
    
public:
    static void FindMatch(OrderBook* _orderBook, Order& _order);
};
