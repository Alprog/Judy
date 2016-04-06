
#pragma once

#include "Singleton.h"
#include <string>
#include "Shader.h"

class ShaderManager : public Singleton<ShaderManager>
{
public:
    std::unordered_map<std::string, Shader*> vertexShaders;
    std::unordered_map<std::string, Shader*> pixelShaders;

    Shader* GetShader(std::string name, Shader::Type type);

};
