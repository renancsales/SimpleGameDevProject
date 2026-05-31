//
// Created by Renan Costa Sales on 31/05/26.
//

#pragma once

#include <vector>
#include <Block.h>

class GameMap
{
public:
    GameMap();
    ~GameMap();

    void CreateMap(int w, int h);

    Block& getBlockUnsafe(int x, int y);
    Block* getBlockSafe(int x, int y);

    int getWidth() { return m_width; }
    int getHeight() { return m_height; }

private:
    int m_width;
    int m_height;
    std::vector<Block> m_mapData;

};
