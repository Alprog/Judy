#version 450

struct PSInput
{
    vec4 position;
    vec2 uv;
};

layout(set = 0, binding = 0, std140) uniform ConstantBuffer
{
    mat4 MVP;
} _47;

layout(location = 0) out vec4 _entryPointOutput;
layout(location = 0) in vec2 uv;

void psmain()
{
    _entryPointOutput = vec4(0.0);
}

