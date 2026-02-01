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
    
public:
    explicit OrderBookWindow(const std::string& _name, OrderBook* _orderBook);
    virtual ~OrderBookWindow();

private:
    void TEMP_CreateNewOrder();

public:
    void Update() override;

    void AddOrderToLog(const Order& _trader);
};