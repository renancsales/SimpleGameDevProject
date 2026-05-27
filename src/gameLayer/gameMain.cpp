//
// Created by Renan Costa Sales on 27/05/26.
//
#include <raylib.h>
#include "gameMain.h"

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
