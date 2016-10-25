
#include "RenderState.h"

#include "Shader.h"
#include "GL/GLShaderImpl.h"
#include <vector>
#include "RenderManager.h"
#include "GL/GLRenderer.h"

RenderState::RenderState()
    : vertexShader {nullptr}
    , pixelShader {nullptr}
    , texture {nullptr}
    , constantBuffer {nullptr}
{
}

void RenderState::link()
{
    programId = glCreateProgram();

    GLRenderer* renderer = (GLRenderer*)RenderManager::getInstance()->getRenderer(RendererType::GL);

    auto vid = renderer->getImpl(vertexShader)->id;
    auto pid = renderer->getImpl(pixelShader)->id;

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
