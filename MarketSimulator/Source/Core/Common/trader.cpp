#include "Core/Common/trader.h"

#include <iostream>
#include <random>


Trader::Trader()
{
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution dist1(1000, 9999);
    static std::uniform_int_distribution dist2(0, 1);

    id_ = dist1(rng);
    direction_ = dist2(rng) == 0 ? EDirection::buyer : EDirection::seller;
    behavior_  = dist2(rng) == 0 ? EBehavior::maker : EBehavior::taker;
    tradePrice_ = 50.0f;
    quantity_ = 1;
}

Trader::Trader(const unsigned int _id)
{
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution dist1(0, 1);

    id_ = _id;
    direction_ = dist1(rng) == 0 ? EDirection::buyer : EDirection::seller;
    behavior_  = dist1(rng) == 0 ? EBehavior::maker : EBehavior::taker;
    tradePrice_ = 50.0f;
    quantity_ = 1;
}

Trader::~Trader() = default;

void Trader::Print() const
{
    std::cout << "id: " << id_ << " | ";
    std::cout << (direction_ == EDirection::buyer ? "buyer" : "seller") << ", "; 
    std::cout << (behavior_ == EBehavior::maker ? "maker" : "taker") << " -> ";
    std::cout << "price: " << tradePrice_ << ", ";
    std::cout << "quantity: " << quantity_ << std::endl;
}

unsigned int Trader::GetId() const
{
    return id_;
}

EDirection Trader::GetDirection() const
{
    return direction_;
}

EBehavior Trader::GetBehavior() const
{
    return behavior_;
}

float Trader::GetTradePrice() const
{
    return tradePrice_;
}

unsigned int Trader::GetQuantity() const
{
    return quantity_;
}
