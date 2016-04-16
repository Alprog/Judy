
#include "GLTextureImpl.h"

#include "Images.h"
#include "../Texture.h"


Impl<Texture, RendererType::GL>::Impl(GLRenderer* renderer, Texture* texture)
    : id {0}
{
    auto image = Images::LoadPng(texture->name);

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, (GLsizei)image->width, (GLsizei)image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->data);

    auto err = glGetError();
    if (err != GL_NO_ERROR)
    {
        printf("ERROR %i!!\n");
        fflush(stdout);
    }

    delete image;
}
