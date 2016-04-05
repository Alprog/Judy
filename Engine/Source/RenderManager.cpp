
#include "RenderManager.h"

#include "DXRenderer.h"
#include "GLRenderer.h"

RenderManager::RenderManager()
{
    renderers.push_back(new DXRenderer());
    renderers.push_back(new GLRenderer());
}
