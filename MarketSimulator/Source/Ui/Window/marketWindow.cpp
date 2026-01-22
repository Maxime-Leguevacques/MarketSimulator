#include "Ui/Window/marketWindow.h"

#include "Finance/Common/bars.h"
#include "imgui/imgui.h"
#include "imgui/implot.h"
#include "Wrapper/implotWrapper.h"


MarketWindow::MarketWindow(const std::string& _name)
    : Window(_name) {}

MarketWindow::~MarketWindow() = default;

void MarketWindow::Update(Market* _market)
{
    dates_.push_back(_market->bars[_market->bars.size() - 1].t);
    
    ImGui::Begin(name.c_str());

    if (ImPlot::BeginPlot("Candlestick Chart", ImGui::GetContentRegionAvail(), ImPlotFlags_Crosshairs))
    {
        ImPlot::SetupAxes(nullptr, nullptr, 0, ImPlotAxisFlags_RangeFit);
        ImPlot::SetupAxesLimits(_market->bars[0].t, _market->bars[_market->bars.size() - 1].t, 0, 50);
        ImPlot::SetupAxisScale(ImAxis_X1, ImPlotScale_Time);
        ImPlot::SetupAxisLimitsConstraints(ImAxis_X1, _market->bars[0].t, _market->bars[_market->bars.size() - 1].t);
        ImPlot::SetupAxisZoomConstraints(ImAxis_X1, 60*60*24*14, _market->bars[_market->bars.size() - 1].t - _market->bars[0].t);
        ImPlot::SetupAxisFormat(ImAxis_Y1, "$%.0f");
        ImplotWrapper::PlotCandlestick("TEST", _market->bars, dates_, static_cast<int>(_market->bars.size()), true, 0.25f, ImVec4(0.000f, 1.000f, 0.441f, 1.000f), ImVec4(0.853f, 0.050f, 0.310f, 1.000f));
        ImPlot::EndPlot();
    }
    
    ImGui::End();
}
