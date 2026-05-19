#include <iostream>
#include <raylib.h>

#include <imgui.h>
#include <rlImGui.h>

int main(int argc, const char * argv[])
{
    std::cout << "resources_path=" << RESOURCES_PATH << std::endl;
    std::cout << "Game Over!!!!\n";

    SetTargetFPS(30);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "Raylib Test");

#pragma region imgui
    rlImGuiSetup(true);
    ImGuiIO& io = ImGui::GetIO();
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable keyboard controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // enable gamepad controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // enable docking
    io.FontGlobalScale = 1.5f;
#pragma endregion

    int posX = 30, posY = 30;
    int size = 100;
    float slider_val = 0.0f;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(GRAY);
        // Rl Imgui
        rlImGuiBegin();
        ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
        ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg,{});
        ImGui::DockSpaceOverViewport(0,ImGui::GetMainViewport());
        ImGui::PopStyleColor(2);

        DrawRectangle(posX, posY, size,size,BLUE);
        DrawText("Hi!!!", 190, 200, 30, RED);
        posX+=1;

#pragma region imgui windows
        // Testing imgui
        ImGui::Begin("Settings");
        ImGui::Text("hello");
        //ImGui::ShowDemoWindow();

        // Note: For every widget, imgui needs an unique name
        if (ImGui::Button("button"))
        {
            std::cout << "button pressed" << std::endl;
        }
        ImGui::SameLine();
        ImGui::PushID(2);
        if (ImGui::Button("button"))
        {
            std::cout << "second button pressed" << std::endl;
        }
        ImGui::PopID();
        ImGui::End();

        // New window
        ImGui::Begin("new window");
        ImGui::Text("hello world");
        ImGui::Separator();
        ImGui::NewLine();
        ImGui::SliderFloat("value", &slider_val, 0.1f, 10.0f);

        ImGui::End();
#pragma endregion

        rlImGuiEnd();
        EndDrawing();
    }

    rlImGuiShutdown();
    CloseWindow();

    return 0;
}