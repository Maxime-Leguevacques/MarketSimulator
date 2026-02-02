#pragma once

#include <deque>

#include "Core/orderBook.h"
#include "Core/Common/order.h"
#include "UI/window.h"


struct SOrderRow
{
    unsigned int traderId;
    EDirection side;
    double price;
    unsigned int quantity;
};


class OrderBookWindow : public Window
{
private:
    std::deque<SOrderRow> orderLog_;

    unsigned int ocount_ = 0;
    OrderBook* orderBook_;

    bool isFill_ = true;
    
public:
    explicit OrderBookWindow(const std::string& _name, OrderBook* _orderBook);
    virtual ~OrderBookWindow();

public:
    void Update() override;

    void AddOrderToLog(const Order& _trader);
};