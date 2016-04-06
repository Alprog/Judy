
#include "Shader.h"
#include "RenderManager.h"
#include "Renderer.h"

Shader::Shader(std::string source, Type type)
    : source {source}
    , type {type}
    , impl {}
{
    Load();
}

void Shader::Load()
{
    auto& renderers = RenderManager::Instance()->renderers;
    for (size_t i = 0; i < renderers.size(); i++)
    {
        if (impl[i] == nullptr)
        {
            impl[i] = renderers[i]->CreateShader(this);
        }
    }
}
