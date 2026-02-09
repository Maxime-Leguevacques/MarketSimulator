#include "UI/Window/orderBookWindow.h"

#include "Core/Common/order.h"
#include "imgui/imgui.h"
#include "imgui/implot.h"


OrderBookWindow::OrderBookWindow(const std::string& _name, OrderBook* _orderBook)
    : Window(_name), orderBook_(_orderBook) {}

OrderBookWindow::~OrderBookWindow() = default;

void OrderBookWindow::Update()
{
    ImGui::Begin(name.c_str());

    while (!orderBook_->newOrders.empty())
    {
        const Order& order = orderBook_->newOrders.front();
        AddOrderToLog(order);
        orderBook_->newOrders.pop();
    }

#pragma region Basic_buttons
    if (ImGui::Button("new order"))
    {
        const Order order(ocount_);
        order.Print();

        // Add to order book
        orderBook_->AddOrder(order);
        
        ocount_++;
    }

    if (ImGui::Button("print order book"))
    {
        orderBook_->Print();
    }
#pragma endregion Basic_buttons


#pragma region Order_book_log
    constexpr ImGuiTableFlags logTableFlags =
        ImGuiTableFlags_Borders |
        ImGuiTableFlags_RowBg |
        ImGuiTableFlags_ScrollY |
        ImGuiTableFlags_Resizable;

    ImGui::SetNextWindowSize(ImVec2(0, ImGui::GetContentRegionAvail().y * 0.5f), ImGuiCond_Always);
    ImGui::BeginChild("Log Table Child", ImVec2(0, ImGui::GetContentRegionAvail().y * 0.5f), ImGuiChildFlags_ResizeY);
    
    // Mouse scroll zoom while pressing CTRL
    if (ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows) && ImGui::GetIO().KeyCtrl)
    {
        logZoom_ += ImGui::GetIO().MouseWheel * 0.1f;
        logZoom_ = std::clamp(logZoom_, 0.7f, 2.5f);
    }

    ImGui::SetWindowFontScale(logZoom_);
    
    ImGui::Text("Log Table");

    if (ImGui::BeginTable("Log Table", 4, logTableFlags))
    {
        ImGui::TableSetupColumn("Trader");
        ImGui::TableSetupColumn("Side");
        ImGui::TableSetupColumn("Price");
        ImGui::TableSetupColumn("Quantity");
        ImGui::TableHeadersRow();

        for (const auto& [traderId, side, price, quantity] : orderLog_)
        {
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%u", traderId);

            ImGui::TableSetColumnIndex(1);
            ImGui::TextColored(
                side == EDirection::buyer
                    ? ImVec4(0, 1, 0, 1)
                    : ImVec4(1, 0, 0, 1),
                side == EDirection::buyer ? "BUY" : "SELL"
            );

            ImGui::TableSetColumnIndex(2);
            ImGui::Text("%d", price);

            ImGui::TableSetColumnIndex(3);
            ImGui::Text("%u", quantity);
        }

        ImGui::EndTable();
    }

    ImGui::SetWindowFontScale(1.0f);
    ImGui::EndChild();
#pragma endregion Order_book_log

#pragma region Order_book_depth_chart
    std::vector<double> bidPrices;
    std::vector<double> bidCumQty;
    std::vector<double> askPrices;
    std::vector<double> askCumQty;

    // fill bids
    for (const auto& [price, qty] : orderBook_->bids_)
    {
        bidPrices.push_back(price);
        bidCumQty.push_back(qty);
    }
    // fill asks
    for (const auto& [price, qty] : orderBook_->asks_)
    {
        askPrices.push_back(price);
        askCumQty.push_back(qty);
    }

    ImGui::Text("Depth Chart");

    ImGui::Checkbox("fill", &isFill_);
    
    if (ImPlot::BeginPlot("Depth Chart", ImVec2(-1, -1)))
    {
        ImPlot::SetupAxes("Price", "Cumulative Quantity", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit);

        if (!bidPrices.empty())
        {
            // Draw bid line and fill (fill first
            if (isFill_)
            {
                ImPlot::SetNextFillStyle(ImVec4(0, 1, 0, 0.4f));
                ImPlot::PlotShaded("Bids", bidPrices.data(), bidCumQty.data(), static_cast<int>(bidPrices.size()));
            }
            ImPlot::SetNextLineStyle(ImVec4(0, 1, 0, 1), 2.0f);
            ImPlot::PlotLine("Bids", bidPrices.data(), bidCumQty.data(), static_cast<int>(bidPrices.size()));
        }
        
        if (!askPrices.empty())
        {
            if (isFill_)
            {
                ImPlot::SetNextFillStyle(ImVec4(1, 0, 0, 0.4f));
                ImPlot::PlotShaded("Asks", askPrices.data(), askCumQty.data(), static_cast<int>(askPrices.size()));
            }
            ImPlot::SetNextLineStyle(ImVec4(1, 0, 0, 1), 2.0f);
            ImPlot::PlotLine("Asks", askPrices.data(), askCumQty.data(), static_cast<int>(askPrices.size()));
        }

        ImPlot::EndPlot();
    }

#pragma endregion Order_book_depth_chart

    ImGui::End();
}

void OrderBookWindow::AddOrderToLog(const Order& _order)
{
    orderLog_.push_front({
        .orderId = _order.id,
        .side = _order.direction,
        .price = _order.priceCts,
        .quantity = _order.quantity
    });
}
