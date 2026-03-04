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
                        side == EDirection::buy
                            ? ImVec4(0, 1, 0, 1)
                            : ImVec4(1, 0, 0, 1),
                        side == EDirection::buy ? "BUY" : "SELL"
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
            
            if (ImGui::BeginTable("Price Levels Table", 2, flags))
            {
                ImGui::TableSetupColumn("Price");
                ImGui::TableSetupColumn("Qty");
                ImGui::TableHeadersRow();

                // Sells (highest first)
                for (auto it = orderBook_->sells_.rbegin(); it != orderBook_->sells_.rend(); ++it)
                {
                    unsigned int totalQty = 0;
                    std::queue<SMatchableOrder> temp = it->second;

                    while (!temp.empty())
                    {
                        totalQty += temp.front().qty;
                        temp.pop();
                    }

                    ImGui::TableNextRow();

                    ImGui::TableSetColumnIndex(0);
                    ImGui::TextColored(ImVec4(1,0,0,1), "%u", it->first);

                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text("%u", totalQty);
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

                // Buys (highest first)
                for (const auto& [price, orders] : orderBook_->buys_)
                {
                    unsigned int totalQty = 0;
                    std::queue<SMatchableOrder> temp = orders;

                    while (!temp.empty())
                    {
                        totalQty += temp.front().qty;
                        temp.pop();
                    }

                    ImGui::TableNextRow();

                    ImGui::TableSetColumnIndex(0);
                    ImGui::TextColored(ImVec4(0,1,0,1), "%u", price);

                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text("%u", totalQty);
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
    std::vector<double> buyPrices;
    std::vector<double> buyCumQty;
    std::vector<double> sellPrices;
    std::vector<double> sellCumQty;

    // fill buys
    for (const auto& [price, order] : orderBook_->buys_)
    {
        unsigned int totalQty = 0;
        std::queue<SMatchableOrder> temp = order;
        while (!temp.empty())
        {
            totalQty += temp.front().qty;
            temp.pop();
        }
        buyPrices.push_back(price);
        buyCumQty.push_back(totalQty);
    }
    // fill sells
    for (const auto& [price, order] : orderBook_->sells_)
    {
        unsigned int totalQty = 0;
        std::queue<SMatchableOrder> temp = order;
        while (!temp.empty())
        {
            totalQty += temp.front().qty;
            temp.pop();
        }
        sellPrices.push_back(price);
        sellCumQty.push_back(totalQty);
    }

    ImGui::Text("Depth Chart");

    ImGui::Checkbox("fill", &isFill_);
    ImGui::SameLine();
    ImGui::Checkbox("from 0", &isFrom0_);
    
    if (ImPlot::BeginPlot("Depth Chart", ImVec2(-1, -1)))
    {
        ImPlot::SetupAxes("Price", "Cumulative Quantity", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit);

        if (!buyPrices.empty())
        {
            // Draw buy line and fill (fill first
            if (isFill_)
            {
                ImPlot::SetNextFillStyle(ImVec4(0, 1, 0, 0.4f));
                ImPlot::PlotShaded("Buys", buyPrices.data(), buyCumQty.data(), static_cast<int>(buyPrices.size()));
            }
            ImPlot::SetNextLineStyle(ImVec4(0, 1, 0, 1), 2.0f);
            ImPlot::PlotLine("Buys", buyPrices.data(), buyCumQty.data(), static_cast<int>(buyPrices.size()));
        }
        
        if (!sellPrices.empty())
        {
            if (isFill_)
            {
                ImPlot::SetNextFillStyle(ImVec4(1, 0, 0, 0.4f));
                ImPlot::PlotShaded("Sells", sellPrices.data(), sellCumQty.data(), static_cast<int>(sellPrices.size()));
            }
            ImPlot::SetNextLineStyle(ImVec4(1, 0, 0, 1), 2.0f);
            ImPlot::PlotLine("Sells", sellPrices.data(), sellCumQty.data(), static_cast<int>(sellPrices.size()));
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
        .quantity = _order.qty
    });
}
