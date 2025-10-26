#include "Ui/Window/chartWindow.h"

#include "imgui/imgui.h"
#include "imgui/implot.h"
#include "imgui/implot_internal.h"

namespace MyNewImPlot {

template <typename T>
int BinarySearch(const T* arr, int l, int r, T x) {
    if (r >= l) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == x)
            return mid;
        if (arr[mid] > x)
            return BinarySearch(arr, l, mid - 1, x);
        return BinarySearch(arr, mid + 1, r, x);
    }
    return -1;
}

void PlotCandlestick(const char* label_id, const double* xs, const double* opens, const double* closes, const double* lows, const double* highs, int count, bool tooltip, float width_percent, ImVec4 bullCol, ImVec4 bearCol) {

    // get ImGui window DrawList
    ImDrawList* draw_list = ImPlot::GetPlotDrawList();
    // calc real value width
    double half_width = count > 1 ? (xs[1] - xs[0]) * width_percent : width_percent;

    // custom tool
    if (ImPlot::IsPlotHovered() && tooltip) {
        ImPlotPoint mouse   = ImPlot::GetPlotMousePos();
        mouse.x             = ImPlot::RoundTime(ImPlotTime::FromDouble(mouse.x), ImPlotTimeUnit_Day).ToDouble();
        float  tool_l       = ImPlot::PlotToPixels(mouse.x - half_width * 1.5, mouse.y).x;
        float  tool_r       = ImPlot::PlotToPixels(mouse.x + half_width * 1.5, mouse.y).x;
        float  tool_t       = ImPlot::GetPlotPos().y;
        float  tool_b       = tool_t + ImPlot::GetPlotSize().y;
        ImPlot::PushPlotClipRect();
        draw_list->AddRectFilled(ImVec2(tool_l, tool_t), ImVec2(tool_r, tool_b), IM_COL32(128,128,128,64));
        ImPlot::PopPlotClipRect();
        // find mouse location index
        int idx = BinarySearch(xs, 0, count - 1, mouse.x);
        // render tool tip (won't be affected by plot clip rect)
        if (idx != -1) {
            ImGui::BeginTooltip();
            char buff[32];
            ImPlot::FormatDate(ImPlotTime::FromDouble(xs[idx]),buff,32,ImPlotDateFmt_DayMoYr,ImPlot::GetStyle().UseISO8601);
            ImGui::Text("Day:   %s",  buff);
            ImGui::Text("Open:  $%.2f", opens[idx]);
            ImGui::Text("Close: $%.2f", closes[idx]);
            ImGui::Text("Low:   $%.2f", lows[idx]);
            ImGui::Text("High:  $%.2f", highs[idx]);
            ImGui::EndTooltip();
        }
    }

    // begin plot item
    if (ImPlot::BeginItem(label_id)) {
        // override legend icon color
        ImPlot::GetCurrentItem()->Color = IM_COL32(64,64,64,255);
        // fit data if requested
        if (ImPlot::FitThisFrame()) {
            for (int i = 0; i < count; ++i) {
                ImPlot::FitPoint(ImPlotPoint(xs[i], lows[i]));
                ImPlot::FitPoint(ImPlotPoint(xs[i], highs[i]));
            }
        }
        // render data
        for (int i = 0; i < count; ++i) {
            ImVec2 open_pos  = ImPlot::PlotToPixels(xs[i] - half_width, opens[i]);
            ImVec2 close_pos = ImPlot::PlotToPixels(xs[i] + half_width, closes[i]);
            ImVec2 low_pos   = ImPlot::PlotToPixels(xs[i], lows[i]);
            ImVec2 high_pos  = ImPlot::PlotToPixels(xs[i], highs[i]);
            ImU32 color      = ImGui::GetColorU32(opens[i] > closes[i] ? bearCol : bullCol);
            draw_list->AddLine(low_pos, high_pos, color);
            draw_list->AddRectFilled(open_pos, close_pos, color);
        }

        // end plot item
        ImPlot::EndItem();
    }
}

} // namespace MyImplot

static double dates[] = {1546300800,1546387200,1546473600,1546560000,1546819200,1546905600,1546992000};
static double opens[] = {100, 102, 101, 105, 107, 106, 109};
static double highs[] = {103, 104, 106, 108, 110, 108, 111};
static double lows[]  = {98, 100, 99, 102, 105, 104, 107};
static double closes[] = {102, 101, 105, 107, 106, 107, 110};


ChartWindow::ChartWindow(const std::string& _name)
    : Window(_name)
{}

ChartWindow::~ChartWindow()
{}

void ChartWindow::Update()
{
    ImGui::Begin(name.c_str());

    // Do stuff here
    // ImPlot::ShowDemoWindow();
    if (ImPlot::BeginPlot("Candlestick Chart"))
    {
        ImPlot::SetupAxes(nullptr, nullptr, 0, ImPlotAxisFlags_AutoFit|ImPlotAxisFlags_RangeFit);
        ImPlot::SetupAxesLimits(1, 10, 0, 200);
        ImPlot::SetupAxisScale(ImAxis_X1, ImPlotScale_Time);
        ImPlot::SetupAxisLimitsConstraints(ImAxis_X1, 1546300800, 1571961600);
        ImPlot::SetupAxisZoomConstraints(ImAxis_X1, 60*60*24*14, 1571961600-1546300800);
        ImPlot::SetupAxisFormat(ImAxis_Y1, "$%.0f");
        MyNewImPlot::PlotCandlestick("TEST", dates, opens, closes, lows, highs, 7, false, 0.25f, ImVec4(0.000f, 1.000f, 0.441f, 1.000f), ImVec4(0.853f, 0.050f, 0.310f, 1.000f));
        ImPlot::EndPlot();
    }
    
    ImGui::End();
}
