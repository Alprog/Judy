#version 450

layout(location = 0) out vec4 _entryPointOutput;
layout(location = 0) in vec4 position;

void main()
{
    _entryPointOutput = position;
}