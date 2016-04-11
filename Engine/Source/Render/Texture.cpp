
#include "Texture.h"
#include "Images.h"
#include "RenderManager.h"
#include "Renderer.h"

Texture::Texture(std::string name)
    : name { name }
    , impl {}
{
    Load();
}

void Texture::Load()
{
    auto& renderers = RenderManager::Instance()->renderers;
    for (size_t i = 0; i < renderers.size(); i++)
    {
        if (impl[i] == nullptr)
        {
            impl[i] = renderers[i]->CreateTexture(this);
        }
    }
}
