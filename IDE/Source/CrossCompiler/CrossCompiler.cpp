
#include "CrossCompiler.h"
#include "DefaultResources.h"
#include <glslang/Public/ShaderLang.h>
#include <SPIRV/SpvBuilder.h>
#include <SPIRV/disassemble.h>
#include <SPIRV/GlslangToSpv.h>
#include <sstream>
#include <spirv_glsl.hpp>

const int defaultVersion = 110;

CrossCompiler::CrossCompiler()
{
    glslang::InitializeProcess();
}

QByteArray CrossCompiler::HlslToSpirv(std::string hlslText, Shader::Type type)
{
    auto messagesType = (EShMessages)(EShMsgSpvRules | EShMsgVulkanRules | EShMsgReadHlsl);


    EShLanguage stage;
    switch (type)
    {
        case Shader::Type::Vertex:
            stage = EShLanguage::EShLangVertex;
            break;

        case Shader::Type::Pixel:
            stage = EShLanguage::EShLangFragment;
            break;

        default:
            throw std::exception("Unknown shader type");
    }

    auto program = new glslang::TProgram();
    auto shader = new glslang::TShader(stage);

    const char * text = hlslText.c_str();
    shader->setStrings(&text, 1);

    shader->addEntryPoint("psmain", EShLanguage::EShLangFragment);
    shader->addEntryPoint("vsmain", EShLanguage::EShLangVertex);

    program->addShader(shader);

    if (!shader->parse(&DefaultResources, defaultVersion, false, messagesType))
        throw std::exception(shader->getInfoLog());

    if (!program->link(messagesType))
        throw std::exception(shader->getInfoLog());

    if (!program->mapIO())
        throw std::exception(shader->getInfoLog());

    std::vector<unsigned int> spirvBinary;
    std::string warningsErrors;
    spv::SpvBuildLogger logger;
    glslang::GlslangToSpv(*program->getIntermediate(stage), spirvBinary, &logger);

    auto dataStart = (char*)&spirvBinary[0];
    auto dataLength = spirvBinary.size() * sizeof(unsigned int) / sizeof(char);
    QByteArray data;
    data.append(dataStart, dataLength);
    return data;
}

std::vector<unsigned int> toInternalFormat(QByteArray spirvBinary)
{
    std::vector<unsigned int> data;
    auto size = spirvBinary.count() * sizeof(char) / sizeof(unsigned int);
    data.resize(size);
    memcpy(&data[0], spirvBinary.data(), spirvBinary.count());
    return data;
}

std::string CrossCompiler::SpirvToHumanReadable(QByteArray spirvBinary)
{
    auto data = toInternalFormat(spirvBinary);
    std::stringstream stream;
    spv::Disassemble(stream, data);
    return stream.str();
}

std::string CrossCompiler::SpirvToGlsl(QByteArray spirvBinary)
{
    auto data = toInternalFormat(spirvBinary);
    spirv_cross::CompilerGLSL compiler(data);

    compiler.set_entry_point("main");

    auto options = compiler.get_options();
    options.vulkan_semantics = true;
    compiler.set_options(options);

    auto glslText = compiler.compile();
    return glslText;
}
