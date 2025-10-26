#pragma once

#include <vector>
#include <string>

#include "window.h"
#include "GLFW/glfw3.h"


struct Vector2
{
    float x;
    float y;
};


class UiManager
{
private:
    static std::vector<Window*> windows_;
    
public:
    static Vector2 screenSize;
    static std::string windowName;
    static GLFWwindow* mainWindow;

private:
    // Static class
    UiManager() = delete;
    UiManager(const UiManager&) = delete;
    UiManager(UiManager&&) = delete;
    UiManager& operator=(const UiManager&) = delete;
    UiManager& operator=(UiManager&&) = delete;
    ~UiManager() = delete;


private:
    static void InitWindow();
    static void InitImGui();
    static void SetColorStyles();

    static void BeginDockSpace();
    static void EndDockSpace();
    static void UpdateWindows();
    
public:
    static void Init();
    static void Update();

    static Window* GetWindowByName(const std::string& _name);
};
