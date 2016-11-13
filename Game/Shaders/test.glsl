#version 450

struct PSInput
{
    vec4 position;
    vec2 uv;
};

layout(set = 0, binding = 0, std140) uniform ConstantBuffer
{
    mat4 MVP;
} _83;

layout(location = 0) in vec3 position_;
layout(location = 1) in vec4 uv_;
layout(location = 0) out vec2 uv;

void vsmain()
{
    PSInput result;
    result.position = vec4(position_, 1.0);
    result.uv = vec2(uv_.xy);
    gl_Position = result.position;
    uv = result.uv;
    gl_Position.z = 2.0 * gl_Position.z - gl_Position.w;
}

void vsmain2()
{
    PSInput result;
    result.position = vec4(position_, 1.0);
    result.uv = vec2(uv_.xy);
    result = result.position;
    uv = result.uv;
}

