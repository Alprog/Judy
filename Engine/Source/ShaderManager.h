
#pragma once

#include "Singleton.h"
#include <string>
#include "Render/Shader.h"
#include <unordered_map>

class ShaderManager : public Singleton<ShaderManager>
{
public:
    std::unordered_map<std::string, Shader*> vertexShaders;
    std::unordered_map<std::string, Shader*> pixelShaders;

    Shader* getShader(std::string name, Shader::Type type);

};
