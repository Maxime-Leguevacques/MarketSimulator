#include "UI/Window/chartWindow.h"

#include "imgui/imgui.h"
#include "imgui/implot.h"
#include "Wrapper/implotWrapper.h"


ChartWindow::ChartWindow(const std::string& _name, Chart* _chart)
    : Window(_name), chart_(_chart) {}

ChartWindow::~ChartWindow() = default;

void ChartWindow::Update()
{
    static size_t lastBarCount = 0;

    if (chart_->bars_.size() > lastBarCount)
    {
        for (size_t i = lastBarCount; i < chart_->bars_.size(); ++i)
            dates_.push_back(chart_->bars_[i].t);

        lastBarCount = chart_->bars_.size();
    }

    if (chart_->bars_.empty())
        return;
    
    ImGui::Begin(name.c_str());

    if (ImPlot::BeginPlot("Candlestick Chart", ImGui::GetContentRegionAvail(), ImPlotFlags_Crosshairs))
    {
        // X axis: time, Y axis: price
        ImPlot::SetupAxes(nullptr, nullptr);
    
        // Make X-axis a time axis
        ImPlot::SetupAxisScale(ImAxis_X1, ImPlotScale_Time);
    
        // Set initial axis limits to show the first N bars (or all loaded bars)
        const double tStart = chart_->bars_[0].t;
        const double tEnd = chart_->bars_[0].t + 60*60*24*7;    // show 1 week initially
        ImPlot::SetupAxisLimits(ImAxis_X1, tStart, tEnd, ImPlotCond_Once);
    
        // Set Y-axis limits
        ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 50, ImPlotCond_Once);
    
        // Plot candlesticks
        ImplotWrapper::PlotCandlestick(
            "TEST",
            chart_->bars_,
            dates_,
            static_cast<int>(chart_->bars_.size()),
            true,
            0.25f,
            ImVec4(0.000f, 1.000f, 0.441f, 1.000f),
            ImVec4(0.853f, 0.050f, 0.310f, 1.000f)
        );
    
        ImPlot::EndPlot();
    }
    
    ImGui::End();
}
