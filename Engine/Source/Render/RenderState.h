
#pragma once

class Shader;
class Texture;
class ConstantBuffer;

#include "GL/gl.h"

class RenderState
{
public:
    RenderState();

    Shader* vertexShader;
    Shader* pixelShader;
    Texture* texture;
    ConstantBuffer* constantBuffer;

    void link();

    GLuint programId;
};
