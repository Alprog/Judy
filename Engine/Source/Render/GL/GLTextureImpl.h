
#pragma once

#include "../Impl.h"
#include "gl.h"

class GLRenderer;
class Texture;

template <>
class Impl<Texture, RendererType::GL>
{
public:
    Impl(GLRenderer* renderer, Texture* texture);

    GLuint id;
};
