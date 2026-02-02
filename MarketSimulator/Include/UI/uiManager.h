#pragma once

#include <vector>
#include <string>

#include "window.h"
#include "Core/market.h"
#include "Core/orderBook.h"
#include "GLFW/glfw3.h"


struct Vector2
{
    float x;
    float y;
};

struct Vector2Int
{
    int x;
    int y;
};


class UiManager
{
private:
    Market* market_ = nullptr;
    OrderBook* orderBook_ = nullptr;
    
    std::vector<Window*> windows_;
    
public:
    Vector2Int screenSize;
    std::string windowName;
    GLFWwindow* mainWindow;

public:
    UiManager();
    ~UiManager();

private:
    void InitWindow();
    void InitImGui();
    void SetColorStyles();

    void BeginDockSpace();
    void EndDockSpace();
    void InitWindows();
    void UpdateWindows();
    
public:
    void Init(Market* _market);
    void Update();

    Window* GetWindowByName(const std::string& _name);
};
