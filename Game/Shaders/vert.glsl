#version 450

struct PSInput
{
    vec4 position;
    vec2 uv;
};

layout(set = 0, binding = 0, std140) uniform ConstantBuffer
{
    mat4 MVP;
} _31;

layout(set = 0, binding = 0) uniform texture2D g_texture;
layout(set = 0, binding = 0) uniform sampler g_sampler;

void aaa()
{
    _entryPointOutput = textureLod(sampler2D(g_texture, g_sampler), uv, 0.0);
}

void bbb()
{
    _entryPointOutput = textureLod(sampler2D(g_texture, g_sampler), uv, 0.0);
}

