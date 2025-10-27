#include "Ui/Window/chartWindow.h"

#include "imgui/imgui.h"
#include "imgui/implot.h"
#include "Wrapper/implotWrapper.h"


static double dates[] = {1546300800,1546387200,1546473600,1546560000,1546819200,1546905600,1546992000};
static double opens[] = {100, 102, 101, 105, 107, 106, 109};
static double highs[] = {103, 104, 106, 108, 110, 108, 111};
static double lows[]  = {98, 100, 99, 102, 105, 104, 107};
static double closes[] = {102, 101, 105, 107, 106, 107, 110};


ChartWindow::ChartWindow(const std::string& _name)
    : Window(_name)
{}

ChartWindow::~ChartWindow() = default;

void ChartWindow::Update()
{
    ImGui::Begin(name.c_str());

    // Do stuff here
    if (ImPlot::BeginPlot("Candlestick Chart"))
    {
        ImPlot::SetupAxes(nullptr, nullptr, 0, ImPlotAxisFlags_AutoFit|ImPlotAxisFlags_RangeFit);
        ImPlot::SetupAxesLimits(1, 10, 0, 200);
        ImPlot::SetupAxisScale(ImAxis_X1, ImPlotScale_Time);
        ImPlot::SetupAxisLimitsConstraints(ImAxis_X1, 1546300800, 1571961600);
        ImPlot::SetupAxisZoomConstraints(ImAxis_X1, 60*60*24*14, 1571961600-1546300800);
        ImPlot::SetupAxisFormat(ImAxis_Y1, "$%.0f");
        ImplotWrapper::PlotCandlestick("TEST", dates, opens, closes, lows, highs, 7, true, 0.25f, ImVec4(0.000f, 1.000f, 0.441f, 1.000f), ImVec4(0.853f, 0.050f, 0.310f, 1.000f));
        ImPlot::EndPlot();
    }
    
    ImGui::End();
}
