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

