
#pragma once

#include "Singleton.h"
#include <string>
#include <unordered_map>

class Texture;

class TextureManager : public Singleton<TextureManager>
{
public:
    std::unordered_map<std::string, Texture*> textures;

    Texture* getTexture(std::string name);
};
