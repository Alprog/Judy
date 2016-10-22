
#include "Shader.h"
#include "RenderManager.h"
#include "IRenderer.h"

Shader::Shader(std::string source, Type type)
    : source {source}
    , type {type}
{
    load();
}

void Shader::load()
{
    auto& renderers = RenderManager::getInstance()->renderers;
    for (size_t i = 0; i < renderers.size(); i++)
    {
        renderers[i]->createImpl(this);
    }
}
