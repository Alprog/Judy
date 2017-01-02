
#include "RenderState.h"

#include "Shader.h"
#include "GL/GLShaderImpl.h"
#include "RenderManager.h"
#include "GL/GLRenderer.h"
#include <vector>
#include <unordered_map>
#include "PipelineState.h"

std::unordered_map<PipelineSettings, PipelineState*> states;

RenderState::RenderState()
    : texture {nullptr}
    , constantBuffer {nullptr}
    , pipelineState {nullptr}
{
}

void RenderState::setVertexShader(Shader* shader)
{
    if (pipelineSettings.vertexShader != shader)
    {
        pipelineSettings.vertexShader = shader;
        pipelineState = nullptr;
    }
}

void RenderState::setPixelShader(Shader* shader)
{
    if (pipelineSettings.pixelShader != shader)
    {
        pipelineSettings.pixelShader = shader;
        pipelineState = nullptr;
    }
}

PipelineState* RenderState::getPipelineState()
{
    if (pipelineState == nullptr)
    {
        auto it = states.find(pipelineSettings);
        if (it != states.end())
        {
            pipelineState = it->second;
        }
        else
        {
            pipelineState = new PipelineState(pipelineSettings);
            states[pipelineSettings] = pipelineState;
        }
    }

    return pipelineState;
}
