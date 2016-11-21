
#pragma once

#include <RenderResource.h>
#include <PipelineSettings.h>

class Shader;

class PipelineState
{
public:
    PipelineState(PipelineSettings& pipelineSettings);

    PipelineSettings settings;
};
