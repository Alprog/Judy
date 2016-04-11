
#include "ShaderManager.h"
#include "Render/Shader.h"

Shader* ShaderManager::GetShader(std::string name, Shader::Type type)
{
    auto& shaders = type == Shader::Type::Vertex ? vertexShaders : pixelShaders;

    auto it = shaders.find(name);
    if (it != std::end(shaders))
    {
        return it->second;
    }

    auto shader = new Shader(name, type);
    shaders[name] = shader;
    return shader;
}
