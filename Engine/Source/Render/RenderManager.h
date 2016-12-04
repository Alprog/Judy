
#pragma once

#include "Singleton.h"
#include "RenderResource.h"
#include <queue>
#include <IRenderer.h>

class [[Meta]] RenderManager : public Singleton<RenderManager>
{
public:
    RenderManager();

    bool addRenderer(RendererType type);
    IRenderer* getRenderer(RendererType type);

    [[Ignore]] unsigned int registerResource(IRenderResource* resource);
    [[Ignore]] void unregisterResource(IRenderResource* resource);

    std::vector<IRenderer*> renderers;

private:
    std::vector<IRenderResource*> resources;
    std::queue<unsigned int> freeIds;
};
