
#include "RenderManager.h"

#include "Render/DX/DXRenderer.h"
#include "Render/GL/GLRenderer.h"
#include "Render/Vulkan/VulkanRenderer.h"

RenderManager::RenderManager()
{
    renderers.push_back(new DXRenderer());
    renderers.push_back(new GLRenderer());
    renderers.push_back(new VulkanRenderer());
}

unsigned int RenderManager::RegisterResource(RenderResource* resource)
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

void RenderManager::UnregisterResource(RenderResource* resource)
{
    auto id = resource->id;
    resources[id] = nullptr;
    freeIds.push(id);
}
