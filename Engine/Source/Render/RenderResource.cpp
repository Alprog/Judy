
#include "RenderResource.h"
#include "RenderManager.h"

IRenderResource::IRenderResource()
{
    this->id = RenderManager::getInstance()->registerResource(this);
}

IRenderResource::~IRenderResource()
{
    RenderManager::getInstance()->unregisterResource(this);
}
