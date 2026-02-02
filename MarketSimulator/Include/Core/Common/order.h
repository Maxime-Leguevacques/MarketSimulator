#pragma once


enum EDirection
{
    buyer,
    seller
};

enum EType
{
    limit,
    market
};


class Order
{
private:
    unsigned int id_;
    EDirection direction_;
    EType type_;
    double price_;
    unsigned int quantity_;

public:
    Order();
    Order(unsigned int _id);
    ~Order();

public:
    void Print() const;

    unsigned int GetId() const;
    EDirection GetDirection() const;
    EType GetType() const;
    double GetTradePrice() const;
    unsigned int GetQuantity() const;

    void SetPrice(double _price);
    void SetQuantity(unsigned int _quantity);
};
