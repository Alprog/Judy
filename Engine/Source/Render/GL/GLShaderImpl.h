
#pragma once

class GLRenderer;

#include "../Impl.h"
#include "gl.h"
#include "../Shader.h"

template <>
class Impl<Shader, RendererType::GL>
{
public:
    Impl(GLRenderer* renderer, Shader* shader);

    GLuint id;
};
