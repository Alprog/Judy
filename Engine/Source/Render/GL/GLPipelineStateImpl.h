
#pragma once

#include "gl.h"
#include <Impl.h>
#include <PipelineState.h>

class GLRenderer;

template <>
class Impl<PipelineState, RendererType::GL>
{
public:
    Impl(GLRenderer* renderer, PipelineState* pipelineState);


};
