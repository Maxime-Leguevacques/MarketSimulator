#include "Core/orderBook.h"

#include <iostream>


OrderBook::OrderBook()
{
}

OrderBook::~OrderBook()
{
}

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
