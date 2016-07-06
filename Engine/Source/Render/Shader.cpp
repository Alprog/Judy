
#include "Shader.h"
#include "RenderManager.h"
#include "IRenderer.h"

Shader::Shader(std::string source, Type type)
    : source {source}
    , type {type}
{
    Load();
}

void Shader::Load()
{
    auto& renderers = RenderManager::Instance()->renderers;
    for (size_t i = 0; i < renderers.size(); i++)
    {
        renderers[i]->CreateImpl(this);
    }
}
