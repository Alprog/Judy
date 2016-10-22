
#include "IndexBuffer.h"

#include "RenderManager.h"
#include "IRenderer.h"

IndexBuffer::IndexBuffer()
{
}

void IndexBuffer::Load()
{
    auto& renderers = RenderManager::getInstance()->renderers;
    for (size_t i = 0; i < renderers.size(); i++)
    {
        renderers[i]->createImpl(this);
    }
}
