
#pragma once

#include "Window.h"
#include "Color.h"

#include <unordered_map>

class Renderer
{
public:
    std::unordered_map<std::wstring, void*> textures;

    virtual void Render(Scene* scene, SwapChain* context) = 0;
    virtual void Clear(Color color) = 0;
};
