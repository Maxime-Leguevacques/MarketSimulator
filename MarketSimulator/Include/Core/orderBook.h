#pragma once
#include <map>
#include <queue>

#include "Common/order.h"


class OrderBook
{
private:
    // map is composed with <price, count>
    std::map<double, unsigned int, std::greater<unsigned int>> bids_;
    std::map<double, unsigned int> asks_;

public:
    std::queue<Order> newOrders;
        
public:
    OrderBook();
    ~OrderBook();

private:
    void AddBid(unsigned int _id, double _price, unsigned int _quantity);
    void AddAsk(unsigned int _id, double _price, unsigned int _quantity);

public:
    void Update();

    void AddOrder(const Order& _order);

    void Print();
};
