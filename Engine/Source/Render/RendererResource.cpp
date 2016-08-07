
#include "RendererResource.h"
#include "RenderManager.h"

RenderResource::RenderResource()
{
    this->id = RenderManager::Instance()->RegisterResource(this);
}

RenderResource::~RenderResource()
{
    RenderManager::Instance()->UnregisterResource(this);
}
