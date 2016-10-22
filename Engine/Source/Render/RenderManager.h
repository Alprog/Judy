
#pragma once

#include "Singleton.h"
#include "RendererResource.h"
#include <queue>

class IRenderer;

class RenderManager : public Singleton<RenderManager>
{
public:
    RenderManager();

    IRenderer* getRenderer(RendererType type);

    unsigned int registerResource(RenderResource* resource);
    void unregisterResource(RenderResource* resource);

    std::vector<IRenderer*> renderers;

private:
    std::vector<RenderResource*> resources;
    std::queue<unsigned int> freeIds;
};
