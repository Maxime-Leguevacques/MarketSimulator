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


class Order
{
private:
    unsigned int id_;
    EDirection direction_;
    EBehavior behavior_;
    double price_;
    unsigned int quantity_;

public:
    Order();
    Order(unsigned int _id);
    ~Order();

public:
    void Print() const;

    void SetPrice(double _price);

    unsigned int GetId() const;
    EDirection GetDirection() const;
    EBehavior GetBehavior() const;
    float GetTradePrice() const;
    unsigned int GetQuantity() const;
};