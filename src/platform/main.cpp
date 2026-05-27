#include <iostream>
#include <raylib.h>

#include <imgui.h>
#include <rlImGui.h>

#include <gameMain.h>
#include <asserts.h>

int main(int argc, const char * argv[])
{
#if PRODUCTION_BUILD == 1
    SetTraceLogLevel(LOG_NONE);
#endif

    std::cout << "resources_path=" << RESOURCES_PATH << std::endl;
    std::cout << "Game Over!!!!\n";


    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "Raylib Test");
    //SetExitKey(KEY_NULL); // Disable Esc from closing window
    SetTargetFPS(30);

    // Initialize ImGui
    rlImGuiSetup(true);
    ImGuiIO& io = ImGui::GetIO();
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable keyboard controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // enable gamepad controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // enable docking
    io.FontGlobalScale = 1.5f;

    if (!initGame())
    {
        return 0;
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        // Rl Imgui
        rlImGuiBegin();
        ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
        ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg,{});
        ImGui::DockSpaceOverViewport(0,ImGui::GetMainViewport());
        ImGui::PopStyleColor(2);

        // Game update
        if (!updateGame())
        {
            CloseWindow();
        }

        rlImGuiEnd();
        EndDrawing();
    }

    CloseWindow();
    closeGame();
    rlImGuiShutdown();




    return 0;
}
