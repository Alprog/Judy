
#pragma once

#include <string>

class Shader
{
public:

    Shader(std::string source);

    virtual void Compile();


protected:
    std::string source;

};
