
#include "VertexBuffer.h"

#include "RenderManager.h"
#include "IRenderer.h"

VertexBuffer::VertexBuffer()
{
}

void VertexBuffer::Load()
{
    auto& renderers = RenderManager::instance()->renderers;
    for (size_t i = 0; i < renderers.size(); i++)
    {
        renderers[i]->createImpl(this);
    }
}
