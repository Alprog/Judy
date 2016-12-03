
#pragma once

#include <functional>

class Shader;
class PipelineState;

enum class CullMode : char
{
    None,
    Front,
    Back
};

class PipelineSettings
{
public:
    PipelineSettings();

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

    inline friend bool operator ==(const PipelineSettings& lhs, const PipelineSettings& rhs)
    {
        return lhs.vertexShader == rhs.vertexShader &&
               lhs.pixelShader == rhs.pixelShader;
    }
};

template <>
struct std::hash<PipelineSettings>
{
    size_t operator()(const PipelineSettings &ps) const
    {
        size_t h1 = std::hash<Shader*>()(ps.vertexShader);
        size_t h2 = std::hash<Shader*>()(ps.pixelShader);
        return h1 ^ (h2 << 1);
    }
};
