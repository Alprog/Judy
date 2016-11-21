
#pragma once

#include <Singleton.h>
#include <Shader.h>
#include <Path.h>
#include <ShaderBunch.h>
#include <unordered_map>
#include <string>
#include <memory>

class ShaderManager : public Singleton<ShaderManager>
{
public:
    ShaderBunch* getShaderBunch(Path path);
    Shader* getShader(Path bunchPath, std::string entryPoint);

private:
    std::unordered_map<Path, std::unique_ptr<ShaderBunch>> bunches;
};
