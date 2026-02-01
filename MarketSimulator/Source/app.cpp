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
    orderBook_ = new OrderBook();
    
    uiManager_.Init(market_, orderBook_);
}

void App::Update()
{
    uiManager_.Update();
}
