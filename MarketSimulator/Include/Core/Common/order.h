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
    unsigned int priceCts;
    unsigned int qty;

public:
    Order();
    Order(unsigned int _id);
    Order(std::time_t _time);
    Order(unsigned int _id, std::time_t _time);
    ~Order();

public:
    void Print() const;
};
