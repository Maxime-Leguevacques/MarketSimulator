#pragma once


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
    unsigned int id;
    EDirection direction;
    EType type;
    unsigned int priceCts;
    unsigned int qty;

public:
    Order();
    Order(unsigned int _id);
    ~Order();

public:
    void Print() const;
};
