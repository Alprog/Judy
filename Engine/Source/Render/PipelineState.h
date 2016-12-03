
#pragma once

#include <RenderResource.h>
#include <PipelineSettings.h>

class Shader;

class PipelineState : public RenderResource<PipelineState>
{
public:
    PipelineState(PipelineSettings& pipelineSettings);
    void load();

    PipelineSettings settings;
};
