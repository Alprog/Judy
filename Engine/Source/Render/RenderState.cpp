
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

    GLRenderer* renderer = (GLRenderer*)RenderManager::instance()->renderers[0];

    glAttachShader(programId, renderer->getImpl(vertexShader)->id);
    glAttachShader(programId, renderer->getImpl(pixelShader)->id);
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
