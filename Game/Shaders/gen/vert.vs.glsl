#version 450

struct PSInput
{
    vec4 position;
    vec2 uv;
};

layout(set = 0, binding = 0, std140) uniform ConstantBuffer
{
    mat4 MVP;
} _46;

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 uv;
layout(location = 0) out vec2 uv_1;

void vsmain()
{
    PSInput result;
    result.position = vec4(position, 1.0);
    result.uv = vec2(uv.xy);
    gl_Position = result.position;
    uv_1 = result.uv;
    gl_Position.z = 2.0 * gl_Position.z - gl_Position.w;
}

