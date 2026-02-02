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
    
    ImGui::InputDouble("start price", &market_->assetStartingPrice);
    ImGui::InputScalar("base quantity", ImGuiDataType_U32, &market_->baseStartingQuantity);

    ImGui::End();
}
