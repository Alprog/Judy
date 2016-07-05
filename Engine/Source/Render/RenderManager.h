
#pragma once

#include "Singleton.h"
#include "RendererResource.h"
#include <queue>

class Renderer;

class RenderManager : public Singleton<RenderManager>
{
public:
    RenderManager();

    std::vector<Renderer*> renderers;


    unsigned int RegisterResource(RenderResource* resource);
    void UnregisterResource(RenderResource* resource);

private:
    std::vector<RenderResource*> resources;
    std::queue<unsigned int> freeIds;

};
