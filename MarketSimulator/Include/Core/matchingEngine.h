#pragma once

#include "orderBook.h"


class MatchingEngine
{
private:
    OrderBook* orderBook_ = nullptr;
    
public:
    MatchingEngine(OrderBook* _orderBook);
    ~MatchingEngine();

private:
    void MatchBid(unsigned int& _qty);
    void MatchAsk(unsigned int& _qty);
    void AddBid(double _price, unsigned int& _qty);
    void AddAsk(double _price, unsigned int& _qty);
    
public:
    void Update();
};
