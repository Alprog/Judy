
#pragma once

#include "RenderTarget.h"
#include "Color.h"
#include "Quad.h"

class Node;

#include <unordered_map>

#define __Meta__

class __Meta__ Renderer
{
public:
    std::unordered_map<std::string, void*> textures;

    virtual void DrawQuad(Quad* quad) = 0;

    virtual void Render(Node* scene, RenderTarget* target) = 0;
    virtual void Clear(Color color) = 0;
};
