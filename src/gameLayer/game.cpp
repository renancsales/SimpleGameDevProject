//
// Created by Renan Costa Sales on 27/05/26.
//
#include <raylib.h>
#include "game.h"
#include <raylib.h>

#include <imgui.h>
#include <rlImGui.h>

#include <Utils.h>

#include "raymath.h"


Game::Game(std::string windowName, uint32_t width, uint32_t height)
    : m_windowName(windowName), m_width(width), m_height(height)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(width, height, windowName.c_str());
    SetExitKey(KEY_NULL); // Disable Esc from closing window
    //SetTargetFPS(30);

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

    // Set world size
    m_GameData.worldSizeX = 2000;
    m_GameData.worldSizeY = 1000;

    m_GameData.gameMap.CreateMap(m_GameData.worldSizeX,m_GameData.worldSizeY);
    for (int i = 0; i < m_GameData.worldSizeX; i++)
    {
        for (int j = 0; j < m_GameData.worldSizeY; j++)
        {
            m_GameData.gameMap.getBlockUnsafe(i,j).type = Block::iron;
        }
    }

    m_GameData.gameMap.getBlockUnsafe(0,0).type = Block::dirt;
    m_GameData.gameMap.getBlockUnsafe(1,1).type = Block::grass;
    m_GameData.gameMap.getBlockUnsafe(2,2).type = Block::goldBlock;
    m_GameData.gameMap.getBlockUnsafe(3,3).type = Block::woodLog;
    m_GameData.gameMap.getBlockUnsafe(4,4).type = Block::platform;

    // Load textures
    //m_assetManager.addTexture("dirt", RESOURCES_PATH "dirt.png");
    m_assetManager.addTexture("textures", RESOURCES_PATH "textures.png");
    m_assetManager.addTexture("frame", RESOURCES_PATH "frame.png");

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

    Vector2 topLeftView = GetScreenToWorld2D({0,0}, m_GameData.camera);
    Vector2 bottoRightView = GetScreenToWorld2D({(float)GetScreenWidth(), (float)GetScreenHeight()}, m_GameData.camera);

    int startXView = (int)floorf(topLeftView.x-1);
    int endXView = (int)ceilf(bottoRightView.x+1);
    int startYView = (int)floorf(topLeftView.y-1);
    int endYView = (int)ceilf(bottoRightView.y+1);

    startXView = Clamp(startXView, 0, m_GameData.gameMap.getWidth()-1);
    endXView = Clamp(endXView, 0, m_GameData.gameMap.getWidth()-1);

    startYView = Clamp(startYView, 0, m_GameData.gameMap.getHeight()-1);
    endYView = Clamp(endYView, 0, m_GameData.gameMap.getWidth()-1);

    // Camera movement
    if (IsKeyDown(KEY_LEFT)) m_GameData.camera.target.x -= 7.0f*deltaTime;
    if (IsKeyDown(KEY_RIGHT)) m_GameData.camera.target.x += 7.0f*deltaTime;
    if (IsKeyDown(KEY_UP)) m_GameData.camera.target.y -= 7.0f*deltaTime;
    if (IsKeyDown(KEY_DOWN)) m_GameData.camera.target.y += 7.0f*deltaTime;

    // Frame mouse position
    Vector2 worldPos = GetScreenToWorld2D(GetMousePosition(), m_GameData.camera);
    int blockX = static_cast<int>(floor(worldPos.x));
    int blockY = static_cast<int>(floor(worldPos.y));

    // Break and placement blocks
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        auto b = m_GameData.gameMap.getBlockSafe(blockX, blockY);
        if (b)
            *b = {};
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        auto b = m_GameData.gameMap.getBlockSafe(blockX, blockY);
        if (b)
        {
            b->type = Block::gold;
        }
    }



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

    for (int j = startYView; j < endYView; j++)
    {
        for (int i = startXView; i < endXView; i++)
        {
            auto &b = m_GameData.gameMap.getBlockUnsafe(i,j);
            if (b.type != Block::air)
            {
                float size = 1.0f;
                float posX = i*size;
                float posY = j*size;

                DrawTexturePro(m_assetManager.getTexture("textures"),
                    getTextureAtlas(b.type, 0, 32, 32), // source
                    {posX, posY, size, size}, //dest
                    {0.0f, 0.0f}, // origin (top-left corner)
                    0.0f, // rotation
                    WHITE); // ting
            }
        }
    }

    // Draw selected block
    auto frameTexture = m_assetManager.getTexture("frame");
    DrawTexturePro(m_assetManager.getTexture("frame"),
        {0, 0, (float)frameTexture.width, (float)frameTexture.height},
        {(float)blockX, (float)blockY, 1, 1},
        {0.f , 0.f},
        0.0f,
        WHITE);

    EndMode2D();

    DrawFPS(10,10);
    return true;
}

void Game::closeGame()
{
    CloseWindow();
    rlImGuiShutdown();
}

