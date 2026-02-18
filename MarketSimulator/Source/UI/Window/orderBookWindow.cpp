#include "UI/Window/orderBookWindow.h"

#include <iostream>

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
    #pragma endregion Basic_buttons

    ImGui::BeginChild("Order book table views", ImVec2(-1, 400), ImGuiChildFlags_Borders | ImGuiChildFlags_ResizeY);
    if (ImGui::BeginTabBar("OrderBookTabs"))
    {
        if (ImGui::BeginTabItem("Order Log"))
        {
            #pragma region Order_book_log
            constexpr ImGuiTableFlags logTableFlags =
                ImGuiTableFlags_Borders |
                ImGuiTableFlags_RowBg |
                ImGuiTableFlags_ScrollY |
                ImGuiTableFlags_Resizable;

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
                    ImGui::Text("%u", price);

                    ImGui::TableSetColumnIndex(3);
                    ImGui::Text("%u", quantity);
                }

                ImGui::EndTable();
            }

            ImGui::SetWindowFontScale(1.0f);
            #pragma endregion Order_book_log
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Price Levels"))
        {
            #pragma region Order_book_price_levels
            constexpr ImGuiTableFlags flags =
                ImGuiTableFlags_Borders |
                ImGuiTableFlags_RowBg |
                ImGuiTableFlags_Resizable;

            // Mouse scroll zoom while pressing CTRL
            if (ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows) && ImGui::GetIO().KeyCtrl)
            {
                logZoom_ += ImGui::GetIO().MouseWheel * 0.1f;
                logZoom_ = std::clamp(logZoom_, 0.7f, 2.5f);
            }

            ImGui::SetWindowFontScale(logZoom_);
            
            ImGui::Text("Aggregated Price Levels");

            if (ImGui::BeginTable("Price Levels Table", 2, flags))
            {
                ImGui::TableSetupColumn("Price");
                ImGui::TableSetupColumn("Qty");
                ImGui::TableHeadersRow();

                // Asks (highest first
                for (auto it = orderBook_->asks_.rbegin(); it != orderBook_->asks_.rend(); ++it)
                {
                    ImGui::TableNextRow();

                    ImGui::TableSetColumnIndex(0);
                    ImGui::TextColored(ImVec4(1,0,0,1), "%u", it->first);

                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text("%u", it->second);
                }

                // Separator row
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                // Calculate number of '#' to type to have a nice visual seperator
                const float cellWidth = ImGui::GetContentRegionAvail().x;
                const float charWidth = ImGui::CalcTextSize("#").x;
                const int count = static_cast<int>(cellWidth / charWidth);
                const std::string line(count, '#');
                ImGui::TextUnformatted(line.c_str());
                // Set to next column as well
                ImGui::TableSetColumnIndex(1);
                ImGui::TextUnformatted(line.c_str());

                // Bids (highest first)
                for (const auto& [price, qty] : orderBook_->bids_)
                {
                    ImGui::TableNextRow();

                    ImGui::TableSetColumnIndex(0);
                    ImGui::TextColored(ImVec4(0,1,0,1), "%u", price);

                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text("%u", qty);
                }

                ImGui::EndTable();
            }
            ImGui::SetWindowFontScale(1.0f);
            #pragma endregion Order_book_price_levels
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::EndChild();
    
    
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
    ImGui::SameLine();
    ImGui::Checkbox("from 0", &isFrom0_);
    
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
