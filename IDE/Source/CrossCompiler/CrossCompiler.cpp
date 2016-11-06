
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

QByteArray CrossCompiler::HlslToSpirv(std::string hlslText)
{
    auto messagesType = (EShMessages)(EShMsgSpvRules | EShMsgVulkanRules | EShMsgReadHlsl);
    auto stage = EShLanguage::EShLangVertex;
    auto program = new glslang::TProgram();
    auto shader = new glslang::TShader(stage);

    const char * text = hlslText.c_str();
    shader->setStrings(&text, 1);
    shader->setEntryPoint("main");
    program->addShader(shader);

    //shader->setShiftSamplerBinding(baseSamplerBinding[stage]);
    //shader->setShiftTextureBinding(baseTextureBinding[stage]);
    //shader->setShiftUboBinding(baseUboBinding[stage]);

    bool parsed = shader->parse(&DefaultResources, defaultVersion, false, messagesType);
    printf("parsed %i\n", parsed);

    bool linked = program->link(messagesType);
    printf("linked %i\n", linked);

    bool mappedIO = program->mapIO();
    printf("mappedIO %i\n", mappedIO);

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
    auto glslText = compiler.compile();
    return glslText;
}
