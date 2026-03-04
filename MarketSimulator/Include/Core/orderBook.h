#pragma once
#include <map>
#include <queue>

#include "Common/order.h"


struct SMatchableOrder
{
    unsigned int id;
    unsigned int qty = 0;
};


class OrderBook
{
    friend class OrderBookWindow;
    friend class MatchingEngine;
    
private:
    // map is composed with <price, SMatchableOrder>
    std::map<unsigned int, std::queue<SMatchableOrder>, std::greater<>> buys_;    // bid is buy price
    std::map<unsigned int, std::queue<SMatchableOrder>> sells_;                    // ask is sell price

public:
    std::queue<Order> newOrders;
        
public:
    OrderBook();
    ~OrderBook();

private:
    void AddBid(unsigned int _id, unsigned int _price, unsigned int _qty);
    void AddAsk(unsigned int _id, unsigned int _price, unsigned int _qty);

public:
    void AddOrder(const Order& _order);
};