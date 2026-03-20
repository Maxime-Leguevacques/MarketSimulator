#include "Core/Common/order.h"

#include <iostream>
#include <random>


Order::Order(const unsigned int _id, const std::time_t _time)
{
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution dist(0, 1);

    id = _id;
    epoch = _time;
    direction = dist(rng) == 0 ? EDirection::buy : EDirection::sell;
    type  = dist(rng) == 0 ? EType::limit : EType::market;
    price = 0;
    qty = 1;
}

Order::~Order() = default;

void Order::Print() const
{
    std::cout << "id: " << id << " | ";
    std::cout << "epoch: " << epoch << " | ";
    std::cout << (direction == EDirection::buy ? "buyer" : "seller") << ", "; 
    std::cout << (type == EType::limit ? "limit" : "market") << " -> ";
    std::cout << "price: " << price << ", ";
    std::cout << "quantity: " << qty << std::endl;
}