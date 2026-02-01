#pragma once


enum EDirection
{
    buyer,
    seller
};

enum EBehavior
{
    maker,
    taker
};


class Trader
{
private:
    unsigned int id_;
    EDirection direction_;
    EBehavior behavior_;
    float tradePrice_;
    unsigned int quantity_;

public:
    Trader();
    Trader(unsigned int _id);
    ~Trader();

public:
    void Print() const;

    unsigned int GetId() const;
    EDirection GetDirection() const;
    EBehavior GetBehavior() const;
    float GetTradePrice() const;
    unsigned int GetQuantity() const;
};