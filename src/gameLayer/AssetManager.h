//
// Created by Renan Costa Sales on 31/05/26.
//
#pragma once

#include <string>
#include <unordered_map>

#include <raylib.h>

class AssetManager
{
public:
    AssetManager() = default;

    void addTexture(const std::string& name, const std::string& path)
    {
        m_textures.emplace(name, LoadTexture(path.c_str()));
    }

    Texture &getTexture(const std::string& textureName)  {return m_textures[textureName];}

    void freeAllTextures()
    {
        for (auto& texture : m_textures)
        {
            UnloadTexture(texture.second);
        }

    }


private:
    std::unordered_map<std::string,Texture> m_textures;

};
