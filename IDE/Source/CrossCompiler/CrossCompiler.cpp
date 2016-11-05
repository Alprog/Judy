
#include "CrossCompiler.h"
#include "DefaultResources.h"
#include <glslang/Public/ShaderLang.h>
#include <SPIRV/SpvBuilder.h>
#include <SPIRV/disassemble.h>
#include <SPIRV/GlslangToSpv.h>

const int defaultVersion = 110;

CrossCompiler::CrossCompiler()
{
    glslang::InitializeProcess();
}

void CrossCompiler::Translate(std::string hlslText)
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

    glslang::OutputSpvHex(spirvBinary, "hex.txt");
    glslang::OutputSpvBin(spirvBinary, "spv.txt");

    spv::Disassemble(std::cout, spirvBinary);
}
