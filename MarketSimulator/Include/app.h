#pragma once

#include "Finance/market.h"
#include "Ui/uiManager.h"


class App
{
private:
    Market* market_ = nullptr;
    UiManager uiManager_;
    
public:
    bool isInExe;
    
public:
    App();
    ~App();

public:
    void Init();
    void Update();
};
