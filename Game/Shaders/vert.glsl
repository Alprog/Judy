#version 450

struct PSInput
{
    vec4 position;
    vec2 uv;
};

layout(set = 0, binding = 0, std140) uniform ConstantBuffer
{
    mat4 MVP;
} _29;

layout(set = 0, binding = 0) uniform texture2D g_texture;
layout(set = 0, binding = 0) uniform sampler g_sampler;

