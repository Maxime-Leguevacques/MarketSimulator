#include "Finance/market.h"

#include <iostream>


Market::Market() = default;

Market::~Market() = default;

void Market::Update()
{
    if (bars.size() < 10)
    {
        // Create new bar
        const Bar bar = {idx, 10.0f, 12.0f, 7.0f, 9.0f, 100.0f, 8};
        bars.push_back(bar);
        idx += 86400;
    }
    
    std::cout << bars.size() << std::endl;
}
