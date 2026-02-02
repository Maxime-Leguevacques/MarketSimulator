#include "Core/Common/order.h"

#include <iostream>
#include <random>


Order::Order()
{
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution dist1(1000, 9999);
    static std::uniform_int_distribution dist2(0, 1);

    id_ = dist1(rng);
    direction_ = dist2(rng) == 0 ? EDirection::buyer : EDirection::seller;
    type_  = dist2(rng) == 0 ? EType::limit : EType::market;
    price_ = 50.0f;
    quantity_ = 1;
}

Order::Order(const unsigned int _id)
{
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution dist(0, 1);

    id_ = _id;
    direction_ = dist(rng) == 0 ? EDirection::buyer : EDirection::seller;
    type_  = dist(rng) == 0 ? EType::limit : EType::market;
    price_ = 0.0f;
    quantity_ = 1;
}

Order::~Order() = default;

void Order::Print() const
{
    std::cout << "id: " << id_ << " | ";
    std::cout << (direction_ == EDirection::buyer ? "buyer" : "seller") << ", "; 
    std::cout << (type_ == EType::limit ? "limit" : "market") << " -> ";
    std::cout << "price: " << price_ << ", ";
    std::cout << "quantity: " << quantity_ << std::endl;
}

unsigned int Order::GetId() const
{
    return id_;
}

EDirection Order::GetDirection() const
{
    return direction_;
}

EType Order::GetType() const
{
    return type_;
}

double Order::GetTradePrice() const
{
    return price_;
}

unsigned int Order::GetQuantity() const
{
    return quantity_;
}

void Order::SetPrice(const double _price)
{
    price_ = _price;
}

void Order::SetQuantity(const unsigned int _quantity)
{
    quantity_ = _quantity;
}