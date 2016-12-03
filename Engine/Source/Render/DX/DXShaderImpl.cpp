
#include "DXShaderImpl.h"
#include <ShaderBunch.h>
#include <Utils.h>
#include <d3dcompiler.h>
#include <codecvt>

Impl<Shader, RendererType::DX>::Impl(DXRenderer* renderer, Shader* shader)
{
    auto& source = shader->bunch->getSourceText(ShaderBunch::BlobType::Hlsl);

    auto entryPoint = shader->entryPoint.c_str();
    auto target = shader->type == ShaderType::Vertex ? "vs_5_0" : "ps_5_0";
    UINT compileFlags = 0;

    auto result = D3DCompile(source.data(), source.size(), entryPoint, nullptr, nullptr, entryPoint, target, compileFlags, 0, &blob, nullptr);

    if (FAILED(result)) throw;
}
