
#include "PipelineState.h"
#include <RenderManager.h>

PipelineState::PipelineState(PipelineSettings& pipelineSettings)
    : settings {pipelineSettings}
{
    load();
}

void PipelineState::load()
{
    auto& renderers = RenderManager::getInstance()->renderers;
    for (size_t i = 0; i < renderers.size(); i++)
    {
        renderers[i]->createImpl(this);
    }
}
