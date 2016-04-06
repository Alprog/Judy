
#include "RenderState.h"

#include "Shader.h"
#include "GLShaderImpl.h"
#include <vector>

void RenderState::link()
{
    programId = glCreateProgram();
    glAttachShader(programId, static_cast<GLShaderImpl*>(vertexShader->impl[1])->id);
    glAttachShader(programId, static_cast<GLShaderImpl*>(pixelShader->impl[1])->id);
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
