#include "UI/Window/orderBookWindow.h"

#include "Core/Common/order.h"
#include "imgui/imgui.h"
#include "imgui/implot.h"


OrderBookWindow::OrderBookWindow(const std::string& _name, OrderBook* _orderBook)
    : Window(_name), orderBook_(_orderBook) {}

OrderBookWindow::~OrderBookWindow() = default;

void OrderBookWindow::TEMP_CreateNewOrder()
{
    const Order order(ocount_);
    order.Print();

    // Add to order book
    orderBook_->AddOrder(order);
    AddOrderToLog(order);
        
    ocount_++;
}

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
        AddOrderToLog(order);
        
        ocount_++;
    }

    if (ImGui::Button("print order book"))
    {
        orderBook_->Print();
    }
#pragma endregion Basic_buttons
 
#pragma region Order_book_log
    ImGui::Text("Log Table");

    constexpr ImGuiTableFlags logTableFlags =
        ImGuiTableFlags_Borders |
        ImGuiTableFlags_RowBg |
        ImGuiTableFlags_ScrollY |
        ImGuiTableFlags_Resizable;

    ImGui::BeginChild("Log Table Child", ImVec2(0, 700), ImGuiChildFlags_ResizeY);

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
            ImGui::Text("%.2f", price);

            ImGui::TableSetColumnIndex(3);
            ImGui::Text("%u", quantity);
        }

        ImGui::EndTable();
    }

    ImGui::EndChild();
#pragma endregion Order_book_log

#pragma region Order_book_depth_chart
    std::vector<double> bidPrices;
    std::vector<double> bidCumQty;
    std::vector<double> askPrices;
    std::vector<double> askCumQty;

    double cumulative = 0.0;
    // fill bids
    for (const auto& [price, qty] : orderBook_->bids_)
    {
        cumulative += qty;
        bidPrices.push_back(price);
        bidCumQty.push_back(cumulative);
    }
    cumulative = 0.0;
    // fill asks
    for (const auto& [price, qty] : orderBook_->asks_)
    {
        cumulative += qty;
        askPrices.push_back(price);
        askCumQty.push_back(cumulative);
    }

    

    ImGui::Text("Depth Chart");
    
    if (ImPlot::BeginPlot("Depth Chart", ImVec2(-1, -1)))
    {
        ImPlot::SetupAxes("Price", "Cumulative Quantity", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit);

        ImPlot::SetNextLineStyle(ImVec4(0, 1, 0, 1), 2.0f);
        if (!bidPrices.empty())
            ImPlot::PlotLine("Bids", bidPrices.data(), bidCumQty.data(), static_cast<int>(bidPrices.size()));

        ImPlot::SetNextLineStyle(ImVec4(1, 0, 0, 1), 2.0f);
        if (!askPrices.empty())
            ImPlot::PlotLine("Asks", askPrices.data(), askCumQty.data(), static_cast<int>(askPrices.size()));
        
        ImPlot::EndPlot();
    }

#pragma endregion Order_book_depth_chart

    ImGui::End();
}

void OrderBookWindow::AddOrderToLog(const Order& _trader)
{
    orderLog_.push_front({
        .traderId = _trader.GetId(),
        .side = _trader.GetDirection(),
        .price = _trader.GetTradePrice(),
        .quantity = _trader.GetQuantity()
    });
}
