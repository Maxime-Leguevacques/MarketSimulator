#include "Ui/Window/chartWindow.h"

#include "imgui/imgui.h"


ChartWindow::ChartWindow(const std::string& _name)
    : Window(_name)
{}

ChartWindow::~ChartWindow()
{}

void ChartWindow::Update()
{
    ImGui::Begin(name.c_str());
    // Do stuff here
    ImGui::End();
}
