
#pragma once

#include <vector>
#include <string>

class CrossShader
{
public:



    std::string hlslText;
    std::vector<unsigned int> spirvBinary;
    std::string sprivText;
    std::string glslText;
    std::string metalText;
};
