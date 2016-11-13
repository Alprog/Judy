#version 450

struct PSInput2
{
    vec4 position;
    vec2 uv;
};

struct PSInput
{
    vec4 position;
    vec2 uv;
};

layout(set = 0, binding = 0, std140) uniform ConstantBuffer
{
    mat4 MVP;
} _64;

layout(location = 0) in vec3 position;
layout(location = 0) out vec2 uv;

void vsmain()
{
    PSInput2 result;
    result.position = vec4(position, 1.0);
    gl_Position = result.position;
    uv = result.uv;
    gl_Position.z = 2.0 * gl_Position.z - gl_Position.w;
}

void vsmain2()
{
    PSInput result;
    result.position = vec4(position, 1.0);
    gl_Position = result.position;
    uv = result.uv;
}

void psmain()
{
    _entryPointOutput = vec4(0.0, 1.0, 1.0, 1.0);
}

