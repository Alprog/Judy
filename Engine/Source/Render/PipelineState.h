
#pragma once

#include "RendererResource.h"

enum class CullMode : char
{
    None,
    Front,
    Back
};

class Shader;

class PipelineState
{
public:
    Shader* vertexShader;
    Shader* pixelShader;

    union
    {
        struct
        {
            CullMode cullMode : 2;
        };
        unsigned int flags;
    };
};
