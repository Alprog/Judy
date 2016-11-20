
#include "GLShaderImpl.h"

#include "GLRenderer.h"
#include "ShaderBunch.h"

#include <fstream>
#include <sstream>
#include <iostream>

Impl<Shader, RendererType::GL>::Impl(GLRenderer* renderer, Shader* shader)
{
    auto isVerts = shader->type == ShaderType::Vertex;
    auto blobType = isVerts ? ShaderBunch::BlobType::GlslVertex : ShaderBunch::BlobType::GlslPixel;

    auto defineLine = "#define " + shader->entryPoint + " main\n";
    auto source = defineLine + shader->bunch->getSourceText(blobType);

    auto sourceBuffer = source.c_str();
    id = glCreateShader(isVerts ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
    glShaderSource(id, 1, &sourceBuffer, nullptr);
    glCompileShader(id);

    GLint isCompiled;
    glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

        auto a = (char*)glGetString(GL_VERSION);

        // --

        glDeleteShader(id);
        id = 0;
    }
}
