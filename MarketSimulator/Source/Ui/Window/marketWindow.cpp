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
    static size_t lastBarCount = 0;

    if (_market->bars.size() > lastBarCount)
    {
        for (size_t i = lastBarCount; i < _market->bars.size(); ++i)
            dates_.push_back(_market->bars[i].t);

        lastBarCount = _market->bars.size();
    }

    if (_market->bars.empty())
        return;
    
    ImGui::Begin(name.c_str());

    if (ImPlot::BeginPlot("Candlestick Chart", ImGui::GetContentRegionAvail(), ImPlotFlags_Crosshairs))
    {
        // X axis: time, Y axis: price
        ImPlot::SetupAxes(nullptr, nullptr);
    
        // Make X-axis a time axis
        ImPlot::SetupAxisScale(ImAxis_X1, ImPlotScale_Time);
    
        // Set initial axis limits to show the first N bars (or all loaded bars)
        double t_start = _market->bars[0].t;
        double t_end = _market->bars[0].t + 60*60*24*7; // show 1 week initially
        ImPlot::SetupAxisLimits(ImAxis_X1, t_start, t_end, ImPlotCond_Once);
    
        // Set Y-axis limits
        ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 50, ImPlotCond_Once);
    
        // Plot candlesticks
        ImplotWrapper::PlotCandlestick(
            "TEST",
            _market->bars,
            dates_,
            static_cast<int>(_market->bars.size()),
            true,
            0.25f,
            ImVec4(0.000f, 1.000f, 0.441f, 1.000f),
            ImVec4(0.853f, 0.050f, 0.310f, 1.000f)
        );
    
        ImPlot::EndPlot();
    }
    
    ImGui::End();
}
