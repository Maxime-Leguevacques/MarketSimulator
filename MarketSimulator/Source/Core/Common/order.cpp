#include "Core/Common/order.h"

#include <iostream>
#include <random>


Order::Order()
{
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution dist1(1000, 9999);
    static std::uniform_int_distribution dist2(0, 1);

    id = dist1(rng);
    direction = dist2(rng) == 0 ? EDirection::buyer : EDirection::seller;
    type  = dist2(rng) == 0 ? EType::limit : EType::market;
    priceCts = 50.0f;
    quantity = 1;
}

Order::Order(const unsigned int _id)
{
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution dist(0, 1);

    id = _id;
    direction = dist(rng) == 0 ? EDirection::buyer : EDirection::seller;
    type  = dist(rng) == 0 ? EType::limit : EType::market;
    priceCts = 0;
    quantity = 1;
}

Order::~Order() = default;

void Order::Print() const
{
    std::cout << "id: " << id << " | ";
    std::cout << (direction == EDirection::buyer ? "buyer" : "seller") << ", "; 
    std::cout << (type == EType::limit ? "limit" : "market") << " -> ";
    std::cout << "price: " << priceCts << ", ";
    std::cout << "quantity: " << quantity << std::endl;
}