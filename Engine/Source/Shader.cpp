
#include "Shader.h"

Shader::Shader(std::string source)
    : source {source}
{
    Compile();
}
