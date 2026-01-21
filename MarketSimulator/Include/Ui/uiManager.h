#pragma once

#include <vector>
#include <string>

#include "window.h"
#include "Finance/market.h"
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
    void UpdateWindows(Market* _market);
    
public:
    void Init(Market* _market);
    void Update();

    Window* GetWindowByName(const std::string& _name);
};
