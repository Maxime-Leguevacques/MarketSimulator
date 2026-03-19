#include "UI/Window/chartWindow.h"

#include "imgui/imgui.h"
#include "imgui/implot.h"
#include "Wrapper/implotWrapper.h"


ChartWindow::ChartWindow(const std::string& _name, Chart* _chart)
    : Window(_name), chart_(_chart) {}

ChartWindow::~ChartWindow() = default;

void ChartWindow::Update()
{
    ImGui::Begin(name.c_str());

    if (chart_->bars_.empty())
    {
        ImGui::End();
        return;
    }
    
    if (ImPlot::BeginPlot("Candlestick Chart", ImGui::GetContentRegionAvail(), ImPlotFlags_Crosshairs))
    {
        // X axis: time, Y axis: price
        ImPlot::SetupAxes(nullptr, nullptr);
        
        // Make X-axis a time axis
        ImPlot::SetupAxisScale(ImAxis_X1, ImPlotScale_Time);

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