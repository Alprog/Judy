
#pragma once

#include "Singleton.h"

class Renderer;

class RenderManager : public Singleton<RenderManager>
{
public:
    RenderManager();

    std::vector<Renderer*> renderers;
};
