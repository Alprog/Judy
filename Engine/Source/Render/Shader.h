
#pragma once

#include <RenderResource.h>
#include <ShaderType.h>
#include <string>

class ShaderBunch;

class Shader : public RenderResource<Shader>
{
public:
    Shader(ShaderBunch* bunch, ShaderType type, std::string entryPoint);
    void load();

public:
    ShaderBunch* bunch;
    ShaderType type;
    std::string entryPoint;
};
