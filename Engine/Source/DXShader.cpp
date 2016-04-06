
#include "Shader.h"
#include "DXShader.h"
#include "d3dcompiler.h"
#include <codecvt>

DXShader::DXShader(std::string source, Shader::Type type)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    auto wsource = converter.from_bytes(source.c_str());

    UINT compileFlags = 0;

    auto entryPoint = type == Shader::Type::Vertex ? "VSMain" : "PSMain";
    auto target = type == Shader::Type::Vertex ? "vs_5_0" : "ps_5_0";

    auto result = D3DCompileFromFile(wsource.c_str(), nullptr, nullptr, entryPoint, target, compileFlags, 0, &blob, nullptr);
    if (FAILED(result)) throw;
}
