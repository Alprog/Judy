
#include "GLPipelineStateImpl.h"
#include <GLRenderer.h>

Impl<PipelineState, RendererType::GL>::Impl(GLRenderer* renderer, PipelineState* pipelineState)
{
    programId = glCreateProgram();

    auto vid = renderer->getImpl(pipelineState->settings.vertexShader)->id;
    auto pid = renderer->getImpl(pipelineState->settings.pixelShader)->id;

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
