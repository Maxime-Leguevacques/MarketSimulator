#include "Core/orderBook.h"

#include "Core/matchingEngine.h"


OrderBook::OrderBook() = default;

OrderBook::~OrderBook() = default;

void OrderBook::AddBid(const unsigned int  _id, const unsigned int _price, const unsigned int _qty)
{
    const SMatchableOrder mo = { .id = _id, .qty = _qty };
    bids_[_price].push(mo);
}

void OrderBook::AddAsk(const unsigned int _id, const unsigned int _price, const unsigned int _qty)
{
    const SMatchableOrder mo = { .id = _id, .qty = _qty };
    asks_[_price].push(mo);
}

void OrderBook::AddOrder(const Order& _order)
{
    newOrders.push(_order);

    Order incoming = _order;

    // Add to order book
    _order.direction == EDirection::buyer
        ? AddBid(_order.id, _order.priceCts, _order.quantity)
        : AddAsk(_order.id, _order.priceCts, _order.quantity);

    MatchingEngine::FindMatch(this, incoming);
}