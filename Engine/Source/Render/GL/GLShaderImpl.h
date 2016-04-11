
#pragma once

class GLRenderer;
class Shader;

#include "../Impl.h"
#include "gl.h"

template <>
class Impl<Shader, RendererType::GL>
{
public:
    Impl(GLRenderer* renderer, Shader* shader);

    GLuint id;
};
