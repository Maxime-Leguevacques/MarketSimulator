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

    ImGui::AlignTextToFramePadding();
    ImGui::Text("interval");
    ImGui::SameLine();

    bool intervalChanged = false;
    
    // Interval change. Calculate minimal width needed for combo box
    const float width = ImGui::CalcTextSize(intervalItems[chart_->selectedInterval_]).x + 25;
    ImGui::SetNextItemWidth(width);
    if (ImGui::Combo("##interval", &chart_->selectedInterval_, intervalItems, IM_ARRAYSIZE(intervalItems)))
    {
        chart_->interval = static_cast<EInterval>(chart_->selectedInterval_);
        dates_.clear();
        intervalChanged = true;
    }
    
    if (chart_->bars_.empty())
    {
        ImGui::End();
        return;
    }
    
    static size_t lastBarCount = 0;

    if (intervalChanged || chart_->bars_.size() != lastBarCount)
    {
        dates_.resize(chart_->bars_.size());
        for (size_t i = 0; i < chart_->bars_.size(); ++i)
            dates_[i] = chart_->bars_[i].to;
    }

    lastBarCount = chart_->bars_.size();
        
    if (ImPlot::BeginPlot("Candlestick Chart", ImGui::GetContentRegionAvail(), ImPlotFlags_Crosshairs))
    {
        // X axis: time, Y axis: price
        ImPlot::SetupAxes(nullptr, nullptr);
        
        // ImPlot::SetupAxisFormat(ImAxis_X1, );

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