#version 440

struct PSInput
{
    vec4 position;
    vec2 uv;
};

layout(binding = 0, std140) uniform ConstantBuffer
{
    mat4 MVP;
} _50;

layout(location = 0) out vec4 _entryPointOutput;
layout(location = 0) in vec2 uv;

void psmain()
{
    _entryPointOutput = vec4(1.0, 0.0, 0.0, 1.0);
}

