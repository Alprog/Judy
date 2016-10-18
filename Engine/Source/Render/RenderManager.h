
#pragma once

#include "Singleton.h"
#include "RendererResource.h"
#include <queue>

class IRenderer;

class RenderManager : public Singleton<RenderManager>
{
public:
    RenderManager();

    std::vector<IRenderer*> renderers;

    unsigned int registerResource(RenderResource* resource);
    void unregisterResource(RenderResource* resource);

private:
    std::vector<RenderResource*> resources;
    std::queue<unsigned int> freeIds;

};
