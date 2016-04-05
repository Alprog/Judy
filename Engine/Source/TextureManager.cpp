
#include "TextureManager.h"
#include "Texture.h"
#include "Images.h"

Texture* TextureManager::GetTexture(std::string name)
{
    auto it = textures.find(name);
    if (it != std::end(textures))
    {
        return it->second;
    }

    Image* image = Images::LoadPng(name);

    return nullptr;
}
