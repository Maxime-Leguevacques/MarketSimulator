#pragma once

#include "Core/chart.h"
#include "Core/market.h"
#include "UI/uiManager.h"


class App
{
private:
    Market* market_ = nullptr;
    Chart* chart_ = nullptr;
    UiManager uiManager_;
    
public:
    bool isInExe;
    
public:
    App();
    ~App();

public:
    void Init();
    void Run();
};
