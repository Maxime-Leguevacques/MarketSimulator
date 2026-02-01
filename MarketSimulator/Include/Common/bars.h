#pragma once

#include <cstdint>


struct Bar
{
    int32_t t;      // epoch time open
    int32_t T;      // epoch time close
    float o;        // open price
    float h;        // high price
    float l;        // low price
    float c;        // close price
    float v;        // volume
    int n;          // number of trades

    Bar() = default;
    ~Bar() = default;
    constexpr Bar(const int32_t _t, int32_t _T, const float _o, const float _h, const float _l, const float _c, const float _v, const int _n)
    : t(_t), T(_T), o(_o), h(_h), l(_l), c(_c), v(_v), n(_n)
        {}
};
