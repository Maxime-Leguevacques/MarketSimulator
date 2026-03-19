#include "Core/orderBook.h"

#include "Core/matchingEngine.h"


OrderBook::OrderBook() = default;

OrderBook::~OrderBook() = default;

void OrderBook::AddBuy(const unsigned int  _id, const unsigned int _price, const unsigned int _qty)
{
    const SMatchableOrder mo = { .id = _id, .qty = _qty };
    buys_[_price].push(mo);
}

void OrderBook::AddSell(const unsigned int _id, const unsigned int _price, const unsigned int _qty)
{
    const SMatchableOrder mo = { .id = _id, .qty = _qty };
    sells_[_price].push(mo);
}

int OrderBook::AddOrder(const Order& _order)
{
    newOrders.push(_order);

    Order incoming = _order;

    // Add to order book
    _order.direction == EDirection::buy
        ? AddBuy(_order.id, _order.price, _order.qty)
        : AddSell(_order.id, _order.price, _order.qty);

    return MatchingEngine::FindMatch(this, incoming);
}