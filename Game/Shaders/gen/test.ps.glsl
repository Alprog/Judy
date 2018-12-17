#version 320 es
precision mediump float;

struct PSInput
{
    vec4 position;
    vec2 uv;
};

layout(binding = 0, std140) uniform ConstantBuffer
{
    mat4 MVP;
} _25;

uniform sampler2D _67;

layout(location = 0) out vec4 _entryPointOutput;
layout(location = 0) in vec2 uv;

void psmain()
{
    _entryPointOutput = texture(_67, uv);
}

