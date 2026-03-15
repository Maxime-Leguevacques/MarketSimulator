#include "app.h"

#include <iostream>


App::App()
{
#ifdef _DEBUG
    isInExe = false;
#else
    isInExe = true;
#endif

    std::cout << "Running in " << (isInExe ? "release." : "debug.") << std::endl;
}

App::~App() = default;

void App::Init()
{
    market_ = new Market();
    chart_ = new Chart(market_);
    
    uiManager_.Init(market_, chart_);
}

void App::Run()
{
    uiManager_.Run();
}
