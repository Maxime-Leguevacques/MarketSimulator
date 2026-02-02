#pragma once
#include <map>
#include <queue>

#include "Common/order.h"


class OrderBook
{
    friend class OrderBookWindow;
    
private:
    // map is composed with <price, quantity>
    std::map<double, unsigned int, std::greater<double>> bids_;    // bid is buy price
    std::map<double, unsigned int> asks_;                          // ask is sell price

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
