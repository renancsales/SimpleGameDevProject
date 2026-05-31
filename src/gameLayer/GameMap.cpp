//
// Created by Renan Costa Sales on 31/05/26.
//
#include <GameMap.h>
#include <asserts.h>

GameMap::GameMap()
    : m_width(0), m_height(0)
{
}

GameMap::~GameMap()
{
}

void GameMap::CreateMap(int w, int h)
{
    m_mapData.resize(w * h);
    m_width = w;
    m_height = h;

    // Clear all block data
    for (auto& block : m_mapData)
    {
        block = {};
    }
}

Block& GameMap::getBlockUnsafe(int x, int y)
{
    permaAssertCommentDevelopement(m_mapData.size()==m_width * m_height, "Map data not initialized");

    permaAssertCommentDevelopement(x < m_width && y < m_height, "Map out of bounds");

    return m_mapData[y * m_width + x];
}

Block* GameMap::getBlockSafe(int x, int y)
{
    permaAssertCommentDevelopement(m_mapData.size()==m_width * m_height, "Map data not initialized");
    if (x < 0 || x >= m_width || y < 0 || y >= m_height)
        return nullptr;

    return &m_mapData[y * m_width + x];
}
