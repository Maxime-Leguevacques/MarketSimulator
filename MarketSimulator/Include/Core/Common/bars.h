#pragma once

#include <cstdint>


struct Bar
{
    uint32_t t;     // epoch time open
    float o;        // open price
    float h;        // high price
    float l;        // low price
    float c;        // close price
    float v;        // volume
    int n;          // number of trades

    Bar() = default;
    ~Bar() = default;
    constexpr Bar(
        const uint32_t _openTime,
        const float _openPrice,
        const float _highPrice,
        const float _lowPrice,
        const float _closePrice,
        const float _volume,
        const int _numberOfTrades)
    :
    t(_openTime),
    o(_openPrice), 
    h(_highPrice), 
    l(_lowPrice), 
    c(_closePrice), 
    v(_volume), 
    n(_numberOfTrades)
        {}
};
