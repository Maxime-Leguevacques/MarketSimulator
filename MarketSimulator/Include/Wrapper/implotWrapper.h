#pragma once
#include <span>
#include <vector>

#include "imgui/imgui.h"


struct Bar;


class ImplotWrapper
{
private:
    static int FindIndex(std::span<const double> _dates, double _x);
    
    template <typename T>
    static int BinarySearch(const T* _arr, int _l, int _r, const T& _x)
    {
        if (_r >= _l)
        {
            int mid = _l + (_r - _l) / 2;
            if (_arr[mid] == _x)
                return mid;
            if (_arr[mid] > _x)
                return BinarySearch(_arr, _l, mid - 1, _x);
            return BinarySearch(_arr, mid + 1, _r, _x);
        }
        return -1;
    }

    template <typename T>
    static int BinarySearch(std::span<const T> _arr, const T& _x)
    {
        return BinarySearch(_arr.data(), 0, static_cast<int>(_arr.size()) - 1, _x);
    }
    
public:
    static void PlotCandlestickOld(
        const char* _labelId, 
        const double* _xs, 
        const double* _opens, 
        const double* _closes, 
        const double* _lows, 
        const double* _highs, 
        int _count, 
        bool _tooltip, 
        float _widthPercent, 
        ImVec4 _bullCol, 
        ImVec4 _bearCol);

    static void PlotCandlestickOldSimple(
        const char* _labelId, 
        const double* _xs, 
        const double* _opens, 
        const double* _closes, 
        const double* _lows, 
        const double* _highs, 
        int _count, 
        bool _tooltip, 
        float _widthPercent, 
        ImVec4 _bullCol, 
        ImVec4 _bearCol);

    static void PlotCandlestickNew(
        const char* _labelId, 
        const std::span<const Bar> _bars,
        const std::span<const double> _dates,
        int _count, 
        bool _tooltip, 
        float _widthPercent, 
        ImVec4 _bullCol, 
        ImVec4 _bearCol);
};
