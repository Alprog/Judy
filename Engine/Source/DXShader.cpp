
#include "DXShader.h"
#include "d3dcompiler.h"
#include <codecvt>

void DXShader::Compile()
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    auto wsource = converter.from_bytes(source.c_str());

    UINT compileFlags = 0;
    auto result = D3DCompileFromFile(wsource.c_str(), nullptr, nullptr, "VSMain", "vs_5_0", compileFlags, 0, &blob, nullptr);
    if (FAILED(result)) throw;
}
