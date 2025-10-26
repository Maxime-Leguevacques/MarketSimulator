#include "app.h"

#include <iostream>

#include "Ui/uiManager.h"


App::App()
{
#ifdef _DEBUG
    isInExe = false;
#else
    isInExe = true;
#endif
    
    std::cout << "Running in " << (isInExe ? "release." : "debug.") << std::endl;
}

App::~App() {}

void App::Start()
{
    UiManager::Init();
}

void App::Run()
{
    UiManager::Update();
}
