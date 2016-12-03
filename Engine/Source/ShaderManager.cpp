
#include "ShaderManager.h"
#include <Shader.h>
#include <ShaderBunch.h>

ShaderBunch* ShaderManager::getShaderBunch(Path path)
{
    auto it = bunches.find(path);
    if (it != bunches.end())
        return it->second.get();

    auto bunch = new ShaderBunch(path);
    bunches[path] = std::unique_ptr<ShaderBunch>(bunch);
    return bunch;
}


Shader* ShaderManager::getShader(Path bunchPath, std::string entryPoint)
{
    return getShaderBunch(bunchPath)->getShader(entryPoint);
}
