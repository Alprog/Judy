
#pragma once

#include "Scene.h"
#include "RenderTarget.h"

#include "Color.h"

#include <unordered_map>

class Renderer
{
public:
    std::unordered_map<std::wstring, void*> textures;

    virtual void Render(Scene* scene, RenderTarget* target) = 0;
    virtual void Clear(Color color) = 0;
};
