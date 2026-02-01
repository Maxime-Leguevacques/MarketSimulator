#include "Core/chart.h"


Chart::Chart() = default;

Chart::~Chart() = default;

void Chart::Update()
{
    if (bars_.size() >= 100)
        return;

    // Create new bar
    const Bar bar = {idx_, 10.0f, 12.0f, 7.0f, 9.0f, 100.0f, 8};
    bars_.push_back(bar);
    idx_ += 86400;
}
