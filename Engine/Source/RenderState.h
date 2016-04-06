
#pragma once

class Shader;
class Texture;

#include "gl.h"

class RenderState
{
public:
    Shader* vertexShader;
    Shader* pixelShader;
    Texture* texture;

    void link();

    GLuint programId;
};
