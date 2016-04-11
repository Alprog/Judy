
#include "TextureManager.h"
#include "Render/Texture.h"
#include "Images.h"

Texture* TextureManager::GetTexture(std::string name)
{
    auto it = textures.find(name);
    if (it != std::end(textures))
    {
        return it->second;
    }

    auto texture = new Texture(name);
    textures[name] = texture;
    return texture;
}
