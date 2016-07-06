
#include "DXShaderImpl.h"
#include "d3dcompiler.h"
#include <codecvt>

Impl<Shader, RendererType::DX>::Impl(DXRenderer* renderer, Shader* shader)
{
    auto filename = shader->source + ".hlsl";

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    auto wfilename = converter.from_bytes(filename);

    UINT compileFlags = 0;

    auto entryPoint = shader->type == Shader::Type::Vertex ? "VSMain" : "PSMain";
    auto target = shader->type == Shader::Type::Vertex ? "vs_5_0" : "ps_5_0";

    auto result = D3DCompileFromFile(wfilename.c_str(), nullptr, nullptr, entryPoint, target, compileFlags, 0, &blob, nullptr);
    if (FAILED(result)) throw;
}
