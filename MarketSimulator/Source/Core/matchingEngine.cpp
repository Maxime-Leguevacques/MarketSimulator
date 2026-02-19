#include "Core/matchingEngine.h"


void MatchingEngine::MatchBid(OrderBook* _orderBook, Order& _order)
{
    // while (_order.quantity > 0 && !_orderBook->asks_.empty())
    // {
    //     auto n = _orderBook->asks_.begin();
    //
    //     
    // }
}

void MatchingEngine::MatchAsk(OrderBook* _orderBook, Order& _order)
{
}

void MatchingEngine::FindMatch(OrderBook* _orderBook, Order& _order)
{
    _order.direction == EDirection::buyer ? MatchBid(_orderBook, _order) : MatchAsk(_orderBook, _order);
}
