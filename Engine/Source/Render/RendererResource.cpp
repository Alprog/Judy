
#include "RendererResource.h"
#include "RenderManager.h"

RenderResource::RenderResource()
{
    this->id = RenderManager::getInstance()->registerResource(this);
}

RenderResource::~RenderResource()
{
    RenderManager::getInstance()->unregisterResource(this);
}
