
#pragma once

class GLRenderer;
class Shader;

#include "gl.h"

class GLShaderImpl
{
public:
    GLShaderImpl(GLRenderer* renderer, Shader* shader);

    GLuint id;
};
