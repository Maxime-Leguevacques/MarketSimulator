#include "UI/Window/simulationSettingsWindow.h"

#include "imgui/imgui.h"


SimulationSettingsWindow::SimulationSettingsWindow(const std::string& _name, Market* _market)
    : Window(_name), market_(_market) {}

SimulationSettingsWindow::~SimulationSettingsWindow() = default;

void SimulationSettingsWindow::Update()
{
    ImGui::Begin(name.c_str());
    
    if (ImGui::InputDouble("start price", &market_->assetStartingPrice))
    {
        
    }

    ImGui::End();
}
