
#include "IndexBuffer.h"

#include "RenderManager.h"
#include "Renderer.h"

void IndexBuffer::Load()
{
    auto& renderers = RenderManager::Instance()->renderers;
    for (size_t i = 0; i < renderers.size(); i++)
    {
        if (impl[i] == nullptr)
        {
            impl[i] = renderers[i]->CreateIndexBuffer(this);
        }
    }
}
