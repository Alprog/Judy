
#include "GLShaderImpl.h"

#include "GLRenderer.h"
#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

GLShaderImpl::GLShaderImpl(GLRenderer* renderer, Shader* shader)
{
    auto isVerts = shader->type == Shader::Type::Vertex;

    auto path = shader->source + (isVerts ? ".vs" : ".ps");

    std::ifstream fstream { path };
    if (fstream.is_open() )
    {
        std::stringstream buffer;
        buffer << fstream.rdbuf();
        auto string = buffer.str();

        const char* source = string.c_str();

        id = glCreateShader(isVerts ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
        glShaderSource(id, 1, &source, nullptr);
        glCompileShader(id);

        GLint isCompiled;
        glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> errorLog(maxLength);
            glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

            // --

            glDeleteShader(id);
            id = 0;
        }
    }


}
