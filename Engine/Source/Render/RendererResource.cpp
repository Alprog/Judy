
#include "RendererResource.h"
#include "RenderManager.h"

RenderResource::RenderResource()
{
    this->id = RenderManager::instance()->registerResource(this);
}

RenderResource::~RenderResource()
{
    RenderManager::instance()->unregisterResource(this);
}
