
#include "Texture.h"
#include "Images.h"
#include "RenderManager.h"
#include "Renderer.h"
#include "Impl.h"

Texture::Texture(std::string name)
    : name { name }
{
    Load();
}

void Texture::Load()
{
    auto& renderers = RenderManager::Instance()->renderers;
    for (size_t i = 0; i < renderers.size(); i++)
    {
        renderers[i]->CreateImpl(this);
    }
}
