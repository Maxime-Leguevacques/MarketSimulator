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
    
    uiManager_.Init(market_);
}

void App::Update()
{
    uiManager_.Update();
}
