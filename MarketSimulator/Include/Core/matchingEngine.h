#pragma once

#include "market.h"
#include "orderBook.h"
#include "Common/order.h"


class MatchingEngine
{
private:
    static Market* market_;
    
public:
    MatchingEngine() = delete;
    ~MatchingEngine() = delete;

private:
    static int MatchBuy(OrderBook* _orderBook, Order& _incoming);
    static int MatchSell(OrderBook* _orderBook, Order& _incoming);
    
public:
    static int FindMatch(OrderBook* _orderBook, Order& _order);
    
    static void SetMarket(Market* _market);
};
