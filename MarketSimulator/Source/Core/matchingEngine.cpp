#include "Core/matchingEngine.h"

#include <iostream>


MatchingEngine::MatchingEngine(OrderBook* _orderBook)
    : orderBook_(_orderBook) {}

MatchingEngine::~MatchingEngine() = default;

void MatchingEngine::MatchBid(unsigned int& _qty)
{
    while (_qty > 0 && !orderBook_->asks_.empty())
    {
        std::map<unsigned int, unsigned int>::iterator bestAsk = orderBook_->asks_.begin();

        if (orderBook_->bids_.empty() || orderBook_->bids_.begin()->first < bestAsk->first)
            break;

        unsigned int matchQty = std::min(_qty, bestAsk->second);

        std::cout << "Trade: " << matchQty << " @ " << bestAsk->first << std::endl;

        _qty -= matchQty;
        bestAsk->second -= matchQty;

        if (bestAsk->second == 0)
            orderBook_->asks_.erase(bestAsk);
    }
}

void MatchingEngine::MatchAsk(unsigned int& _qty)
{
    while (_qty > 0 && !orderBook_->bids_.empty())
    {
        std::map<unsigned int, unsigned int>::iterator bestBid = orderBook_->bids_.begin();

        if (orderBook_->asks_.empty() || bestBid->first < orderBook_->asks_.begin()->first)
            break;

        unsigned int matchQty = std::min(_qty, bestBid->second);

        std::cout << "Trade: " << matchQty << " @ " << bestBid->first << std::endl;

        _qty -= matchQty;
        bestBid->second -= matchQty;

        if (bestBid->second == 0)
            orderBook_->bids_.erase(bestBid);
    }
}

void MatchingEngine::AddBid(double _price, unsigned int& _qty)
{
    MatchBid(_qty);
    if (_qty > 0)
        orderBook_->bids_[_price] += _qty;
}

void MatchingEngine::AddAsk(double _price, unsigned int& _qty)
{
    MatchAsk(_qty);
    if (_qty > 0)
        orderBook_->asks_[_price] += _qty;
}

void MatchingEngine::Update()
{
    if (!orderBook_->bids_.empty())
    {
        std::map<unsigned int, unsigned int>::iterator bestBid = orderBook_->bids_.begin();
        std::cout << "Best Bid: " << bestBid->first << " qty=" << bestBid->second << std::endl;
    }
    else
    {
        std::cout << "Best Bid: EMPTY" << std::endl;
    }

    if (!orderBook_->asks_.empty())
    {
        std::map<unsigned int, unsigned int>::iterator bestAsk = orderBook_->asks_.begin();
        std::cout << "Best Ask: " << bestAsk->first << " qty=" << bestAsk->second << std::endl;
    }
    else
    {
        std::cout << "Best Ask: EMPTY" << std::endl;
    }
}
