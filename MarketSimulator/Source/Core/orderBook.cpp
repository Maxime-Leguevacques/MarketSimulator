#include "Core/orderBook.h"

#include <iostream>


OrderBook::OrderBook() = default;

OrderBook::~OrderBook() = default;

void OrderBook::Update()
{
}

void OrderBook::AddBid(const unsigned int  _id, const double _price, const unsigned int _quantity)
{
    bids_[_price] += _quantity;
}

void OrderBook::AddAsk(const unsigned int _id, const double _price, const unsigned int _quantity)
{
    asks_[_price] += _quantity;
}

void OrderBook::AddOrder(const Order& _order)
{
    newOrders.push(_order);

    // Add to order book
    _order.GetDirection() == EDirection::buyer
        ? AddBid(_order.GetId(), _order.GetTradePrice(), _order.GetQuantity())
        : AddAsk(_order.GetId(), _order.GetTradePrice(), _order.GetQuantity());
}

void OrderBook::Print()
{
    std::cout << "===== ORDER BOOK =====\n";
    std::cout << "Asks:\n";
    for (auto it = asks_.rbegin(); it != asks_.rend(); ++it)
        std::cout << it->first << " : " << it->second << "\n";

    std::cout << "-----------------\n";

    std::cout << "Bids:\n";
    for (const auto & [fst, snd] : bids_)
        std::cout << fst << " : " << snd << "\n";
    
    std::cout << "================ =====" << std::endl;
}
