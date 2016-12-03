
#include "Shader.h"
#include <RenderManager.h>
#include <IRenderer.h>
#include <ShaderType.h>

Shader::Shader(ShaderBunch* bunch, ShaderType type, std::string entryPoint)
    : bunch{bunch}
    , type{type}
    , entryPoint{entryPoint}
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
