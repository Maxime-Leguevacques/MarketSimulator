#pragma once

#include "Core/market.h"
#include "Core/orderBook.h"
#include "UI/uiManager.h"


class App
{
private:
    Market* market_ = nullptr;
    OrderBook* orderBook_ = nullptr;
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
