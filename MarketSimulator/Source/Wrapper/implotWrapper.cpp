#include <algorithm>

#include "Wrapper/implotWrapper.h"

#include "Core/Common/bars.h"
#include "imgui/implot.h"
#include "imgui/implot_internal.h"


int ImplotWrapper::FindIndex(std::span<const double> _dates, const double _x)
{
    const auto it = std::ranges::lower_bound(_dates, _x);
    const size_t idx = it == _dates.end() ? _dates.size() - 1 : it - _dates.begin();
    return static_cast<int>(idx);
}

void ImplotWrapper::PlotCandlestick(
    const char* _labelId, 
    const std::span<const Bar> _bars,
    const std::span<const double> _dates,
    const int _count,
    const bool _tooltip,
    const float _widthPercent,
    const ImVec4 _bullCol,
    const ImVec4 _bearCol)
{
    // Get ImGui window DrawList
    ImDrawList* drawList = ImPlot::GetPlotDrawList();
    // Calculate real value width
    
    const double halfWidth = _count > 1 ? static_cast<float>(_bars[1].t - _bars[0].t) * _widthPercent : 86400.0 * _widthPercent;    // Implot uses days as x value and there are 86400 seconds in a day.
                                                                                                                                    // So we check if we are on first bar to use that seconds value or not

    // custom tool
    if (ImPlot::IsPlotHovered() && _tooltip)
    {
        ImPlotPoint mouse       = ImPlot::GetPlotMousePos();
        mouse.x                 = ImPlot::RoundTime(ImPlotTime::FromDouble(mouse.x), ImPlotTimeUnit_Day).ToDouble();
        const float  toolL      = ImPlot::PlotToPixels(mouse.x - halfWidth * 1.5, mouse.y).x;
        const float  toolR      = ImPlot::PlotToPixels(mouse.x + halfWidth * 1.5, mouse.y).x;
        const float  toolT      = ImPlot::GetPlotPos().y;
        const float  toolB      = toolT + ImPlot::GetPlotSize().y;
        ImPlot::PushPlotClipRect();
        drawList->AddRectFilled(ImVec2(toolL, toolT), ImVec2(toolR, toolB), IM_COL32(128,128,128,64));
        ImPlot::PopPlotClipRect();
        // find mouse location index
        // render tool tip (won't be affected by plot clip rect)
        const int idx = FindIndex(_dates, mouse.x);

        if (idx >= 0 && static_cast<size_t>(idx) < _bars.size())
        {
            ImGui::BeginTooltip();
            char buff[32];
            ImPlot::FormatDate(ImPlotTime::FromDouble(_bars[idx].t), buff, 32, ImPlotDateFmt_DayMoYr, false);
            ImGui::Text("Day:   %s", buff);
            ImGui::Text("Open:  $%.2f", _bars[idx].o);
            ImGui::Text("High:  $%.2f", _bars[idx].h);
            ImGui::Text("Low:   $%.2f", _bars[idx].l);
            ImGui::Text("Close: $%.2f", _bars[idx].c);
            ImGui::EndTooltip();
        }
    }

    // begin plot item
    if (ImPlot::BeginItem(_labelId))
    {
        // override legend icon color
        ImPlot::GetCurrentItem()->Color = IM_COL32(64, 64, 64, 255);
        // fit data if requested
        if (ImPlot::FitThisFrame())
            for (int i = 0; i < _count; ++i)
            {
                ImPlot::FitPoint(ImPlotPoint(_bars[i].t, _bars[i].l));
                ImPlot::FitPoint(ImPlotPoint(_bars[i].t, _bars[i].h));
            }
        
        // render data
        for (int i = 0; i < _count; ++i)
        {
            ImVec2 openPos  = ImPlot::PlotToPixels(_bars[i].t - halfWidth, _bars[i].o);
            ImVec2 closePos = ImPlot::PlotToPixels(_bars[i].t + halfWidth, _bars[i].c);
            ImVec2 lowPos   = ImPlot::PlotToPixels(_bars[i].t, _bars[i].l);
            ImVec2 highPos  = ImPlot::PlotToPixels(_bars[i].t, _bars[i].h);
            const ImU32 color = ImGui::GetColorU32(_bars[i].o > _bars[i].c ? _bearCol : _bullCol);
            drawList->AddLine(lowPos, highPos, color);
            drawList->AddRectFilled(openPos, closePos, color);
        }

        // end plot item
        ImPlot::EndItem();
    }
}
