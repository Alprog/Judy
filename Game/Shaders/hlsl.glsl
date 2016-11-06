#version 450

struct PSInput
{
    vec4 position;
};

layout(set = 0, binding = 0, std140) uniform ConstantBuffer
{
    mat4 MVP;
} _16;

layout(location = 0) in vec4 position;

void main()
{
    PSInput result;
    result.position = (_16.MVP * position);
    gl_Position = result.position;
    gl_Position.z = 2.0 * gl_Position.z - gl_Position.w;
}

