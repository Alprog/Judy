
#include "RenderManager.h"

#if !LINUX
#include "Render/DX/DXRenderer.h"
#include "Render/Vulkan/VulkanRenderer.h"
#endif

#include "Render/GL/GLRenderer.h"

RenderManager::RenderManager()
{
#if !LINUX
    renderers.push_back(new DXRenderer());
    renderers.push_back(new VulkanRenderer());
#endif
    renderers.push_back(new GLRenderer());
}

IRenderer* RenderManager::getRenderer(RendererType type)
{
    for (IRenderer* renderer : renderers)
    {
        if (renderer->getType() == type)
        {
            return renderer;
        }
    }
    return nullptr;
}

unsigned int RenderManager::registerResource(IRenderResource* resource)
{
    unsigned int id;
    if (freeIds.empty())
    {
        id = resources.size();
        resources.push_back(resource);
    }
    else
    {
        id = freeIds.front();
        resources[id] = resource;
        freeIds.pop();
    }
    return id;
}

void RenderManager::unregisterResource(IRenderResource* resource)
{
    auto id = resource->id;
    resources[id] = nullptr;
    freeIds.push(id);
}
