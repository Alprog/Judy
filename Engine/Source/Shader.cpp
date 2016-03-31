
#include "Shader.h"

Shader::Shader(std::string source, Type type)
    : source {source}
    , type {type}
{
    Compile();
}
