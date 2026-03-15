#include "Core/Common/order.h"

#include <iostream>
#include <random>


Order::Order()
{
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution dist1(1000, 9999);
    static std::uniform_int_distribution dist2(0, 1);

    id = dist1(rng);
    epoch = std::time(nullptr);
    direction = dist2(rng) == 0 ? EDirection::buy : EDirection::sell;
    type  = dist2(rng) == 0 ? EType::limit : EType::market;
    priceCts = 50.0f;
    qty = 1;
}

Order::Order(const unsigned int _id)
{
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution dist(0, 1);

    id = _id;
    epoch = std::time(nullptr);
    direction = dist(rng) == 0 ? EDirection::buy : EDirection::sell;
    type  = dist(rng) == 0 ? EType::limit : EType::market;
    priceCts = 0;
    qty = 1;
}

Order::~Order() = default;

void Order::Print() const
{
    std::cout << "id: " << id << " | ";
    std::cout << "epoch: " << epoch << " | ";
    std::cout << (direction == EDirection::buy ? "buyer" : "seller") << ", "; 
    std::cout << (type == EType::limit ? "limit" : "market") << " -> ";
    std::cout << "price: " << priceCts << ", ";
    std::cout << "quantity: " << qty << std::endl;
}