#pragma once
#include <span>

#include "imgui/imgui.h"


struct Bar;


class ImplotWrapper
{
private:
    static int FindIndex(std::span<const double> _dates, double _x);
    
public:
    static void PlotCandlestick(
        const char* _labelId, 
        const std::span<const Bar> _bars,
        const std::span<const double> _dates,
        const int _count, 
        const bool _tooltip, 
        const float _widthPercent, 
        const ImVec4 _bullCol, 
        const ImVec4 _bearCol);
};
