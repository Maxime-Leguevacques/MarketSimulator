#include "UI/Window/marketWindow.h"

#include "Core/Common/bars.h"
#include "imgui/imgui.h"
#include "imgui/implot.h"
#include "Wrapper/implotWrapper.h"


MarketWindow::MarketWindow(const std::string& _name, Market* _market)
    : Window(_name), market_(_market) {}

MarketWindow::~MarketWindow() = default;

void MarketWindow::Update()
{
    static size_t lastBarCount = 0;

    if (market_->bars.size() > lastBarCount)
    {
        for (size_t i = lastBarCount; i < market_->bars.size(); ++i)
            dates_.push_back(market_->bars[i].t);

        lastBarCount = market_->bars.size();
    }

    if (market_->bars.empty())
        return;
    
    ImGui::Begin(name.c_str());

    if (ImPlot::BeginPlot("Candlestick Chart", ImGui::GetContentRegionAvail(), ImPlotFlags_Crosshairs))
    {
        // X axis: time, Y axis: price
        ImPlot::SetupAxes(nullptr, nullptr);
    
        // Make X-axis a time axis
        ImPlot::SetupAxisScale(ImAxis_X1, ImPlotScale_Time);
    
        // Set initial axis limits to show the first N bars (or all loaded bars)
        const double tStart = market_->bars[0].t;
        const double tEnd = market_->bars[0].t + 60*60*24*7;    // show 1 week initially
        ImPlot::SetupAxisLimits(ImAxis_X1, tStart, tEnd, ImPlotCond_Once);
    
        // Set Y-axis limits
        ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 50, ImPlotCond_Once);
    
        // Plot candlesticks
        ImplotWrapper::PlotCandlestick(
            "TEST",
            market_->bars,
            dates_,
            static_cast<int>(market_->bars.size()),
            true,
            0.25f,
            ImVec4(0.000f, 1.000f, 0.441f, 1.000f),
            ImVec4(0.853f, 0.050f, 0.310f, 1.000f)
        );
    
        ImPlot::EndPlot();
    }
    
    ImGui::End();
}
