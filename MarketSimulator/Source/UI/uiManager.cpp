#include "UI/uiManager.h"

#include <iostream>
#include <wtypes.h>

#include "Common/utils.h"
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_internal.h"
#include "imgui/implot.h"
#include "UI/Window/marketWindow.h"
#include "UI/Window/orderBookWindow.h"


UiManager::UiManager() = default;

UiManager::~UiManager() = default;

void UiManager::InitWindow()
{
    // Init window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

    // Get primary monitor
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    // monitor dimensions
    screenSize = {.x = mode->width, .y = mode->height };
    
    mainWindow = glfwCreateWindow(screenSize.x, screenSize.y, windowName.c_str(), nullptr, nullptr);
    if (mainWindow == nullptr)
    {
        std::cerr << Utils::messageTypeError << "Failed to create GLFW window: " << windowName << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(mainWindow); 
}

void UiManager::InitImGui()
{
    // Setup ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.IniFilename = nullptr;    // Erase previous potentially saved configs
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // Setup style
    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        SetColorStyles();
        style.WindowRounding = 4;
        style.FrameRounding = 4;
        style.GrabRounding = 3;
        style.ScrollbarSize = 7;
        style.ScrollbarRounding = 0;
    }

    ImGui_ImplGlfw_InitForOpenGL(mainWindow, true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

void UiManager::SetColorStyles()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;
    
    // Define your purple palette
    constexpr ImVec4 color1 = ImVec4(0.13f, 0.10f, 0.18f, 1.0f); // Very dark purple
    constexpr ImVec4 color2 = ImVec4(0.25f, 0.18f, 0.40f, 1.0f); // Dark purple
    constexpr ImVec4 color3 = ImVec4(0.38f, 0.27f, 0.55f, 1.0f); // Mid purple
    constexpr ImVec4 color4 = ImVec4(0.56f, 0.45f, 0.78f, 1.0f); // Light purple
    constexpr ImVec4 color5 = ImVec4(0.72f, 0.62f, 0.95f, 1.0f); // Lavender (lightest)
    
    // Muted background to prevent eye strain
    constexpr ImVec4 backgroundColor = ImVec4(0.08f, 0.06f, 0.12f, 1.0f);
    
    // Backgrounds
    colors[ImGuiCol_WindowBg]            = backgroundColor;
    colors[ImGuiCol_ChildBg]             = backgroundColor;
    colors[ImGuiCol_PopupBg]             = color1;
    
    // Borders
    colors[ImGuiCol_Border]              = color2;
    colors[ImGuiCol_BorderShadow]        = backgroundColor;
    
    // Text
    colors[ImGuiCol_Text]                = color5;
    colors[ImGuiCol_TextDisabled]        = color3;
    
    // Headers
    colors[ImGuiCol_Header]              = color2;
    colors[ImGuiCol_HeaderHovered]       = color3;
    colors[ImGuiCol_HeaderActive]        = color4;
    
    // Buttons
    colors[ImGuiCol_Button]              = color2;
    colors[ImGuiCol_ButtonHovered]       = color3;
    colors[ImGuiCol_ButtonActive]        = color4;
    
    // Frame
    colors[ImGuiCol_FrameBg]             = color2;
    colors[ImGuiCol_FrameBgHovered]      = color3;
    colors[ImGuiCol_FrameBgActive]       = color4;
    
    // Tabs
    colors[ImGuiCol_Tab]                 = color2;
    colors[ImGuiCol_TabHovered]          = color3;
    colors[ImGuiCol_TabActive]           = color4;
    colors[ImGuiCol_TabUnfocused]        = color1;
    colors[ImGuiCol_TabUnfocusedActive]  = color2;
    
    // Title
    colors[ImGuiCol_TitleBg]             = color1;
    colors[ImGuiCol_TitleBgActive]       = color2;
    colors[ImGuiCol_TitleBgCollapsed]    = color1;
    
    // Resize Grip
    colors[ImGuiCol_ResizeGrip]          = color3;
    colors[ImGuiCol_ResizeGripHovered]   = color4;
    colors[ImGuiCol_ResizeGripActive]    = color5;
    
    // Scrollbar
    colors[ImGuiCol_ScrollbarBg]         = backgroundColor;
    colors[ImGuiCol_ScrollbarGrab]       = color2;
    colors[ImGuiCol_ScrollbarGrabHovered]= color3;
    colors[ImGuiCol_ScrollbarGrabActive] = color4;
    
    // Checkmark, sliders
    colors[ImGuiCol_CheckMark]           = color5;
    colors[ImGuiCol_SliderGrab]          = color4;
    colors[ImGuiCol_SliderGrabActive]    = color5;
    
    // Plots
    colors[ImGuiCol_PlotLines]           = color4;
    colors[ImGuiCol_PlotLinesHovered]    = color5;
    colors[ImGuiCol_PlotHistogram]       = color4;
    colors[ImGuiCol_PlotHistogramHovered]= color5;
    
    // Table
    colors[ImGuiCol_TableHeaderBg]       = color2;
    colors[ImGuiCol_TableBorderStrong]   = color3;
    colors[ImGuiCol_TableBorderLight]    = color2;
    
    // Separator
    colors[ImGuiCol_Separator]           = color3;
    colors[ImGuiCol_SeparatorHovered]    = color4;
    colors[ImGuiCol_SeparatorActive]     = color5;
    
    // Navigation
    colors[ImGuiCol_NavHighlight]           = color4;
    colors[ImGuiCol_NavWindowingHighlight]  = color5;
    colors[ImGuiCol_NavWindowingDimBg]      = backgroundColor;
    
    // Optional: tweak rounding and padding
    style.FrameRounding = 5.0f;
    style.WindowRounding = 5.0f;
    style.GrabRounding = 3.0f;
    style.ScrollbarRounding = 5.0f;
}

void UiManager::BeginDockSpace()
{
#pragma region Setup_dockspace
    bool dockSpaceOpen = true;
    constexpr bool optionFullScreenPersistant = true;

    ImGuiDockNodeFlags dockSpaceFlags = ImGuiDockNodeFlags_None;

    if (optionFullScreenPersistant)
        dockSpaceFlags |= ImGuiDockNodeFlags_PassthruCentralNode;

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

    if (optionFullScreenPersistant)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });
        windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;
    }
#pragma endregion Setup_dockspace

    ImGui::Begin("DockSpace_Window", &dockSpaceOpen, windowFlags);

    // Update toolbar here if implemented

    if (optionFullScreenPersistant)
        ImGui::PopStyleVar(3);

#pragma region Create_dockspace
    const ImGuiID dockspaceId = ImGui::GetID("DockSpace");
    ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), dockSpaceFlags);

    // Dock control space
    static bool isInit = false;
    if (!isInit)
    {
        isInit = true;

        ImGui::DockBuilderRemoveNode(dockspaceId);
        ImGui::DockBuilderAddNode(dockspaceId);
        ImGui::DockBuilderSetNodeSize(dockspaceId, ImGui::GetMainViewport()->Size);

        // Create dockspace layout here
        // Split window from [] to [dock_id_left | dock_id_right]
        ImGuiID dockIdLeft, dockIdRight;
        ImGui::DockBuilderSplitNode(dockspaceId, ImGuiDir_Left, 0.5f, &dockIdLeft, &dockIdRight);
        
        // Setup dockspace here
        ImGui::DockBuilderDockWindow(GetWindowByName("Chart")->name.c_str(), dockIdLeft);
        ImGui::DockBuilderDockWindow(GetWindowByName("OrderBook")->name.c_str(), dockIdRight);

        ImGui::DockBuilderFinish(dockspaceId);
    }
#pragma endregion Create_dockspace
}

void UiManager::EndDockSpace()
{
    ImGui::End();
}

void UiManager::InitWindows()
{
}

void UiManager::UpdateWindows(Market* _market)
{
    for (const auto& window : windows_)
        window->Update();
}

void UiManager::Init(Market* _market, OrderBook* _orderBook)
{
    market_ = _market;
    orderBook_ = _orderBook;
    
    InitWindow();

    windows_.push_back(new MarketWindow("Chart", _market));
    windows_.push_back(new OrderBookWindow("OrderBook", _orderBook));

    InitImGui();
}

void UiManager::Update()
{
    const ImGuiIO& io = ImGui::GetIO();
    glViewport(0, 0, screenSize.x, screenSize.y);

    while (!glfwWindowShouldClose(mainWindow))
    {
        glfwPollEvents();

        glClearColor(0.09f, 0.14f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        BeginDockSpace();

        market_->Update();
        UpdateWindows(market_);

        EndDockSpace();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backupCurrentContext);
        }

        glfwSwapBuffers(mainWindow);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();
    glfwTerminate();
}

Window* UiManager::GetWindowByName(const std::string& _name)
{
    for (const auto& window : windows_)
        if (window->name == _name)
            return window;
    
    std::cerr << Utils::messageTypeError << "No window with the name: " << _name.c_str() << " has been found" << std::endl; 
    return nullptr;
}
