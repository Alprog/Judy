
#pragma once

#include "gl.h"

class GLRenderer;
class Texture;

class GLTextureImpl
{
public:
    GLTextureImpl(GLRenderer* renderer, Texture* texture);

    GLuint id;
};
