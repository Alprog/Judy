
#pragma once

#include "../Impl.h"
#include "gl.h"
#include "../Texture.h"

class GLRenderer;

template <>
class Impl<Texture, RendererType::GL>
{
public:
    Impl(GLRenderer* renderer, Texture* texture);

    GLuint id;
};
