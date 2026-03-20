#pragma once

#include <ctime>


enum EDirection
{
    buy,
    sell
};

enum EType
{
    limit,
    market
};


class Order
{
public:
    std::time_t epoch;
    unsigned int id;
    EDirection direction;
    EType type;
    unsigned int price;
    unsigned int qty;

public:
    Order(unsigned int _id, std::time_t _time);
    ~Order();

public:
    void Print() const;
};
