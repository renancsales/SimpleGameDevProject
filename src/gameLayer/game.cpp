//
// Created by Renan Costa Sales on 27/05/26.
//
#include <raylib.h>
#include "game.h"
#include <raylib.h>

#include <imgui.h>
#include <rlImGui.h>


Game::Game(std::string windowName, uint32_t width, uint32_t height)
    : m_windowName(windowName), m_width(width), m_height(height)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(width, height, windowName.c_str());
    SetExitKey(KEY_NULL); // Disable Esc from closing window
    SetTargetFPS(30);

    // Initialize ImGui
    rlImGuiSetup(true);
    ImGuiIO& io = ImGui::GetIO();
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable keyboard controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // enable gamepad controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // enable docking
    io.FontGlobalScale = 1.5f;

}

Game::~Game()
{

}

void Game::Run()
{

    if (!initGame())
    {
        return;
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground({75,75,150,255});

        // Rl Imgui
        rlImGuiBegin();
        ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
        ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg,{});
        ImGui::DockSpaceOverViewport(0,ImGui::GetMainViewport());
        ImGui::PopStyleColor(2);

        // Game update
        if (!updateGame())
        {
            closeGame();
        }

        rlImGuiEnd();
        EndDrawing();
    }

}

bool Game::initGame()
{
    //m_GameData = {};
    //m_GameData.dirtTexture = LoadTexture(RESOURCES_PATH "dirt.png" );

    m_GameData.gameMap.CreateMap(30,10);
    m_GameData.gameMap.getBlockUnsafe(0,0).type = Block::dirt;
    m_GameData.gameMap.getBlockUnsafe(1,1).type = Block::dirt;
    m_GameData.gameMap.getBlockUnsafe(2,2).type = Block::dirt;
    m_GameData.gameMap.getBlockUnsafe(3,3).type = Block::dirt;
    m_GameData.gameMap.getBlockUnsafe(4,4).type = Block::dirt;

    // Load textures
    m_assetManager.addTexture("dirt", RESOURCES_PATH "dirt.png");

    m_GameData.camera.target = {0.f, 0.f};
    m_GameData.camera.rotation = 0.0f;
    m_GameData.camera.zoom = 100.0f;

    return true;
}

bool Game::updateGame()
{
    float deltaTime = GetFrameTime();
    if (deltaTime > 1.0f/5)
        deltaTime = 1.0f/5.0f;
    m_GameData.camera.offset = {GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};

    BeginMode2D(m_GameData.camera);

    // Camera movement
    if (IsKeyDown(KEY_LEFT)) m_GameData.camera.target.x -= 7.0f*deltaTime;
    if (IsKeyDown(KEY_RIGHT)) m_GameData.camera.target.x += 7.0f*deltaTime;
    if (IsKeyDown(KEY_UP)) m_GameData.camera.target.y -= 7.0f*deltaTime;
    if (IsKeyDown(KEY_DOWN)) m_GameData.camera.target.y += 7.0f*deltaTime;

    if (IsKeyDown(KEY_A))
    {
        m_GameData.positionX -=200*deltaTime;
    }
    if (IsKeyDown(KEY_D))
    {
        m_GameData.positionX += 200*deltaTime;
    }
    if (IsKeyDown(KEY_S))
    {
        m_GameData.positionY +=200*deltaTime;
    }
    if (IsKeyDown(KEY_W))
    {
        m_GameData.positionY -= 200*deltaTime;
    }

    //DrawRectangle(m_GameData.positionX, m_GameData.positionY, 50, 50, WHITE);
    auto texture = m_assetManager.getTexture("dirt");
    /*DrawTexturePro(texture,
        {0,0,(float)texture.width,(float)texture.height},
        {m_GameData.positionX,m_GameData.positionY,100,100},{},0, WHITE);*/

    for (int j = 0; j < m_GameData.gameMap.getHeight(); j++)
    {
        for (int i = 0; i < m_GameData.gameMap.getWidth(); i++)
        {
            auto &b = m_GameData.gameMap.getBlockUnsafe(i,j);
            if (b.type != Block::air)
            {
                float size = 1.0f;
                float posX = i*size;
                float posY = j*size;

                DrawTexturePro(m_assetManager.getTexture("dirt"),
                    Rectangle{0.f, 0.f, (float)m_assetManager.getTexture("dirt").width, (float)m_assetManager.getTexture("dirt").height}, // source
                    {posX, posY, size, size}, //dest
                    {0.0f, 0.0f}, // origin (top-left corner)
                    0.0f, // rotation
                    WHITE); // ting
            }
        }
    }

    EndMode2D();
    return true;
}

void Game::closeGame()
{
    CloseWindow();
    rlImGuiShutdown();
}


/*
struct GameData
{
    float positionX = 0.0;
    float positionY = 0.0;
} gameData;


bool initGame()
{
    return true;
}

bool updateGame()
{
    float deltaTime = GetFrameTime();
    if (deltaTime > 1.0f/5)
        deltaTime = 1.0f/5.0f;

    if (IsKeyDown(KEY_A))
    {
        gameData.positionX -=200*deltaTime;
    }
    if (IsKeyDown(KEY_D))
    {
        gameData.positionX += 200*deltaTime;
    }
    if (IsKeyDown(KEY_S))
    {
        gameData.positionY +=200*deltaTime;
    }
    if (IsKeyDown(KEY_W))
    {
        gameData.positionY -= 200*deltaTime;
    }

    DrawRectangle(gameData.positionX, gameData.positionY, 50, 50, WHITE);

    return true;
}

void closeGame()
{
    return;
}
*/
