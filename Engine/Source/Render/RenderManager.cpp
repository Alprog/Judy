
#include "RenderManager.h"

#if !LINUX
#include "Render/DX/DXRenderer.h"
#include "Render/Vulkan/VulkanRenderer.h"
#endif

#include "Render/GL/GLRenderer.h"

RenderManager::RenderManager()
{
}

bool RenderManager::addRenderer(RendererType type)
{
    auto renderer = getRenderer(type);
    if (renderer != nullptr)
    {
        return true;
    }

    switch (type)
    {
#if WIN
        case RendererType::DX:
            renderer = new DXRenderer();
            break;
#endif

#if WIN || LINUX
        case RendererType::Vulkan:
            renderer = new VulkanRenderer();
            break;
#endif

        case RendererType::GL:
            renderer = new GLRenderer();
            break;

        default:
            return false;
    }

    renderers.push_back(renderer);
    return true;
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
