
#include "CrossCompiler.h"
#include "DefaultResources.h"
#include <SPIRV/SpvBuilder.h>
#include <SPIRV/disassemble.h>
#include <SPIRV/GlslangToSpv.h>
#include <sstream>
#include <spirv_glsl.hpp>
#include <Utils.h>

const int defaultVersion = 110;
const EShMessages messagesType = (EShMessages)(EShMsgSpvRules | EShMsgVulkanRules | EShMsgReadHlsl);

std::vector<std::string> shaderTypes {"vs", "gs", "ps"};

EShLanguage toEShLanguage(std::string name)
{
    if (name == "vs") return EShLanguage::EShLangVertex;
    if (name == "gs") return EShLanguage::EShLangGeometry;
    if (name == "ps") return EShLanguage::EShLangFragment;
    return EShLanguage::EShLangCount;
}

CrossCompiler::CrossCompiler()
{
    glslang::InitializeProcess();
}

void addShader(glslang::TProgram& program, std::string& hlslText, EShLanguage stage, std::string entryPointName)
{
    auto shader = new glslang::TShader(stage);

    const char * text = hlslText.c_str();
    shader->setStrings(&text, 1);
    shader->setEntryPoint(entryPointName.c_str());

    program.addShader(shader);

    if (!shader->parse(&DefaultResources, defaultVersion, false, messagesType))
    {
        throw std::exception(shader->getInfoLog());
    }
}

QByteArray getBinary(glslang::TProgram& program, EShLanguage stage)
{
    std::vector<unsigned int> spirvBinary;
    std::string warningsErrors;
    spv::SpvBuildLogger logger;
    glslang::GlslangToSpv(*program.getIntermediate(stage), spirvBinary, &logger);

    auto dataStart = (char*)&spirvBinary[0];
    auto dataLength = spirvBinary.size() * sizeof(unsigned int) / sizeof(char);
    QByteArray data;
    data.append(dataStart, dataLength);
    return data;
}

CrossCompiler::Spirv CrossCompiler::hlslToSpirv(std::string hlslText)
{
    auto program = glslang::TProgram();

    auto entryPoints = getEntryPoints(hlslText);
    for (auto& stageEntries : entryPoints)
    {
        auto stage = toEShLanguage(stageEntries.first);
        for (auto name : stageEntries.second)
        {
            addShader(program, hlslText, stage, name);
        }
    }

    if (!program.link(messagesType))
        throw std::exception(program.getInfoLog());

    Spirv spirv;
    if (entryPoints["vs"].size() > 0)
        spirv.vs = getBinary(program, EShLanguage::EShLangVertex);

    if (entryPoints["ps"].size() > 0)
        spirv.ps = getBinary(program, EShLanguage::EShLangFragment);
    return spirv;
}

std::vector<unsigned int> toInternalFormat(QByteArray spirvBinary)
{
    std::vector<unsigned int> data;
    auto size = spirvBinary.count() * sizeof(char) / sizeof(unsigned int);
    data.resize(size);
    memcpy(&data[0], spirvBinary.data(), spirvBinary.count());
    return data;
}

std::string CrossCompiler::spirvToHumanReadable(QByteArray spirvBinary)
{
    auto data = toInternalFormat(spirvBinary);
    std::stringstream stream;
    spv::Disassemble(stream, data);
    return stream.str();
}

std::string CrossCompiler::spirvToGlsl(QByteArray spirvBinary)
{
    auto data = toInternalFormat(spirvBinary);
    spirv_cross::CompilerGLSL compiler(data);

    auto options = compiler.get_options();
    options.version = 440;
    compiler.set_options(options);

    auto glslText = compiler.compile();
    return glslText;
}

CrossCompiler::EntryPoints CrossCompiler::getEntryPoints(std::string hlslText)
{
    EntryPoints entryPoints;
    for (auto shaderType : shaderTypes)
    {
        entryPoints[shaderType] = {};
    }

    for (auto& pragma : getPragmas(hlslText))
    {
        auto name = pragma.first;
        if (entryPoints.find(name) != entryPoints.end())
        {
            entryPoints[name].push_back(pragma.second);
        }
    }

    return entryPoints;
}

CrossCompiler::Pragmas CrossCompiler::getPragmas(std::string hlslText)
{
    Pragmas pragmas;
    replace(hlslText, "\r", "\n");
    auto lines = split(hlslText, "\n");
    for (auto& line : lines)
    {
        replace(line, "  ", " ");
        if (startsWith(line, "#pragma"))
        {
            auto words = split(line, " ");
            if (words.size() > 1)
            {
                auto name = words[1];
                auto argument = words.size() > 2 ? words[2] : "";
                pragmas.push_back({name, argument});
            }
        }
    }
    return pragmas;
}
