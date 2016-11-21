
#pragma once

#include "Singleton.h"
#include "RenderResource.h"
#include <queue>
#include <IRenderer.h>

class RenderManager : public Singleton<RenderManager>
{
public:
    RenderManager();

    IRenderer* getRenderer(RendererType type);

    unsigned int registerResource(IRenderResource* resource);
    void unregisterResource(IRenderResource* resource);

    std::vector<IRenderer*> renderers;

private:
    std::vector<IRenderResource*> resources;
    std::queue<unsigned int> freeIds;
};
