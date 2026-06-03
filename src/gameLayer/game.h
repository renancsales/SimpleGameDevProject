//
// Created by Renan Costa Sales on 27/05/26.
//
#pragma once

#include <iostream>
#include <raylib.h>
#include <AssetManager.h>
#include <GameMap.h>

struct GameData
{
    float positionX = 0.0;
    float positionY = 0.0;

    int worldSizeX = 2000;
    int worldSizeY = 1000;

    GameMap gameMap;
    Camera2D camera;
} ;

struct FrameData
{
    float timestep = 0.0f;
    float frametime = 0.0f;
    float lastframeTime = 0.0f;
};

class Game
{
public:
    Game(std::string  windowName, uint32_t width, uint32_t height );
    ~Game();
    void Run();

private:
    bool initGame();
    bool updateGame();
    void closeGame();

public:
private:
    FrameData m_frameData;
    std::string m_windowName;
    uint32_t m_width; uint32_t m_height;

    GameData m_GameData;
    AssetManager  m_assetManager;
};

/*
bool initGame();
bool updateGame();
void closeGame();
*/