#include "UI/Window/simulationSettingsWindow.h"

#include "imgui/imgui.h"


SimulationSettingsWindow::SimulationSettingsWindow(const std::string& _name, Market* _market)
    : Window(_name), market_(_market) {}

SimulationSettingsWindow::~SimulationSettingsWindow() = default;

void SimulationSettingsWindow::Update()
{
    ImGui::Begin(name.c_str());

    const std::string playStr = market_->isPlaying ? "pause" : "play";
    if (ImGui::Button(playStr.c_str()))
        market_->isPlaying = !market_->isPlaying;

    ImGui::SliderFloat("time tick speed", &market_->timeTick, 1.0f, 1000.0f);
    ImGui::SliderFloat("order tick speed", &market_->orderTick, 0.1f, 100.0f);
    
    ImGui::InputInt("start price", &market_->assetStartingPriceCts);
    ImGui::InputScalar("base quantity", ImGuiDataType_U32, &market_->baseStartingQuantity);
    
    if (ImGui::Button("Do Order Tick"))
        market_->DoOrderTick();
    
    ImGui::SameLine();
    
    if (ImGui::Button("Do Time Tick"))
        market_->DoTimeTick();

    ImGui::End();
}
