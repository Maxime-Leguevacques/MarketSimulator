#include "Wrapper/implotWrapper.h"

#include "imgui/implot.h"
#include "imgui/implot_internal.h"


void ImplotWrapper::PlotCandlestick(
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
    ImVec4 _bearCol)
{
    // get ImGui window DrawList
    ImDrawList* drawList = ImPlot::GetPlotDrawList();
    // calc real value width
    const double halfWidth = _count > 1 ? (_xs[1] - _xs[0]) * _widthPercent : _widthPercent;

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
        int idx = BinarySearch(_xs, 0, _count - 1, mouse.x);
        // render tool tip (won't be affected by plot clip rect)
        if (idx != -1)
        {
            ImGui::BeginTooltip();
            char buff[32];
            ImPlot::FormatDate(ImPlotTime::FromDouble(_xs[idx]),buff,32,ImPlotDateFmt_DayMoYr,ImPlot::GetStyle().UseISO8601);
            ImGui::Text("Day:   %s",  buff);
            ImGui::Text("Open:  $%.2f", _opens[idx]);
            ImGui::Text("Close: $%.2f", _closes[idx]);
            ImGui::Text("Low:   $%.2f", _lows[idx]);
            ImGui::Text("High:  $%.2f", _highs[idx]);
            ImGui::EndTooltip();
        }
    }

    // begin plot item
    if (ImPlot::BeginItem(_labelId))
    {
        // override legend icon color
        ImPlot::GetCurrentItem()->Color = IM_COL32(64,64,64,255);
        // fit data if requested
        if (ImPlot::FitThisFrame())
            for (int i = 0; i < _count; ++i) {
                ImPlot::FitPoint(ImPlotPoint(_xs[i], _lows[i]));
                ImPlot::FitPoint(ImPlotPoint(_xs[i], _highs[i]));
            }
        
        // render data
        for (int i = 0; i < _count; ++i)
        {
            ImVec2 openPos  = ImPlot::PlotToPixels(_xs[i] - halfWidth, _opens[i]);
            ImVec2 closePos = ImPlot::PlotToPixels(_xs[i] + halfWidth, _closes[i]);
            ImVec2 lowPos   = ImPlot::PlotToPixels(_xs[i], _lows[i]);
            ImVec2 highPos  = ImPlot::PlotToPixels(_xs[i], _highs[i]);
            const ImU32 color = ImGui::GetColorU32(_opens[i] > _closes[i] ? _bearCol : _bullCol);
            drawList->AddLine(lowPos, highPos, color);
            drawList->AddRectFilled(openPos, closePos, color);
        }

        // end plot item
        ImPlot::EndItem();
    }
}
