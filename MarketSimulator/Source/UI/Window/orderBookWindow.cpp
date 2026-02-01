#include "UI/Window/orderBookWindow.h"

#include "Core/Common/trader.h"
#include "imgui/imgui.h"




OrderBookWindow::OrderBookWindow(const std::string& _name, OrderBook* _orderBook)
    : Window(_name), orderBook_(_orderBook) {}

OrderBookWindow::~OrderBookWindow() = default;

void OrderBookWindow::TEMP_CreateNewOrder()
{
    const Trader trader(tcount_);
    trader.Print();

    // Add to order book
    trader.GetDirection() == EDirection::buyer
        ? orderBook_->AddBid(trader.GetId(), trader.GetTradePrice(), trader.GetQuantity())
        : orderBook_->AddAsk(trader.GetId(), trader.GetTradePrice(), trader.GetQuantity());

    AddOrderToLog(trader);
        
    tcount_++;
}

void OrderBookWindow::Update()
{
    ImGui::Begin(name.c_str());

#pragma region Basic_buttons
    if (ImGui::Button("new order"))
    {
        const Trader trader(tcount_);
        trader.Print();

        // Add to order book
        trader.GetDirection() == EDirection::buyer
            ? orderBook_->AddBid(trader.GetId(), trader.GetTradePrice(), trader.GetQuantity())
            : orderBook_->AddAsk(trader.GetId(), trader.GetTradePrice(), trader.GetQuantity());

        AddOrderToLog(trader);
        
        tcount_++;
    }

    if (ImGui::Button("print order book"))
    {
        orderBook_->Print();
    }
#pragma endregion Basic_buttons

#pragma region Order_book_log
    ImGui::Separator();
    ImGui::Text("Order Log");

    constexpr ImGuiTableFlags tableFlags =
        ImGuiTableFlags_Borders |
        ImGuiTableFlags_RowBg |
        ImGuiTableFlags_ScrollY |
        ImGuiTableFlags_Resizable;

    ImGui::BeginChild("OrderTableChild", ImVec2(0, 0), true);

    if (ImGui::BeginTable("OrderTable", 4, tableFlags))
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

    
    ImGui::End();
}

void OrderBookWindow::AddOrderToLog(const Trader& _trader)
{
    orderLog_.push_front({
        .traderId = _trader.GetId(),
        .side = _trader.GetDirection(),
        .price = _trader.GetTradePrice(),
        .quantity = _trader.GetQuantity()
    });
}
