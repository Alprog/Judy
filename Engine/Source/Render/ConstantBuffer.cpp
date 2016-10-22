
#include "ConstantBuffer.h"

#include "RenderManager.h"
#include "IRenderer.h"

ConstantBuffer::ConstantBuffer()
{
    load();
}

void ConstantBuffer::load()
{
    auto& renderers = RenderManager::getInstance()->renderers;
    for (size_t i = 0; i < renderers.size(); i++)
    {
        renderers[i]->createImpl(this);
    }
}
