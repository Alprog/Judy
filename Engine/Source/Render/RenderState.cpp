
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
{
}

void RenderState::link()
{
    programId = glCreateProgram();

    GLRenderer* renderer = (GLRenderer*)RenderManager::getInstance()->getRenderer(RendererType::GL);

    auto vid = renderer->getImpl(pipelineSettings.vertexShader)->id;
    auto pid = renderer->getImpl(pipelineSettings.pixelShader)->id;

    glAttachShader(programId, vid);
    glAttachShader(programId, pid);
    glLinkProgram(programId);

    GLint isLinked;
    glGetProgramiv(programId, GL_LINK_STATUS, &isLinked);
    if(isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetProgramInfoLog(programId, maxLength, &maxLength, &errorLog[0]);

        glDeleteProgram(programId);
        programId = 0;
    }
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
