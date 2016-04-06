
#include "GLShaderImpl.h"

#include "GLRenderer.h"
#include "Shader.h"

#include "gl.h"

#include <fstream>
#include <sstream>
#include <iostream>

GLShaderImpl::GLShaderImpl(GLRenderer* renderer, Shader* shader)
{
    auto path = shader->source + ".vs";

    std::ifstream fstream { path };
    if (fstream.is_open() )
    {
        std::stringstream buffer;
        buffer << fstream.rdbuf();
        auto string = buffer.str();

        const char* source = string.c_str();

        GLuint shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        GLint isCompiled;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> errorLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

            // --

            glDeleteShader(shader);
            return;
        }
    }


}
