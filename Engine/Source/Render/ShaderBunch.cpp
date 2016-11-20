
#include "ShaderBunch.h"
#include <Utils.h>
#include <map>

ShaderBunch::ShaderBunch(Path path)
    : path{path}
{
    auto hlslText = getSourceText(BlobType::Hlsl);

    replace(hlslText, "\r", "\n");
    auto lines = split(hlslText, "\n");
    for (auto& line : lines)
    {
        replace(line, "  ", " ");
        if (startsWith(line, "#pragma"))
        {
            auto words = split(line, " ");
            if (words.size() > 2)
            {
                auto type = words[1];
                auto value = words[2];

                if (type == "vs")
                {
                    entryPoints[value] = ShaderType::Vertex;
                }
                else if (type == "gs")
                {
                    entryPoints[value] = ShaderType::Geometry;
                }
                else if (type == "ps")
                {
                    entryPoints[value] = ShaderType::Pixel;
                }
            }
        }
    }
}

const std::unordered_map<std::string, ShaderType>& ShaderBunch::getEntryPoints()
{
    return entryPoints;
}

const Blob& ShaderBunch::getSource(BlobType type)
{
    if (blobs[type] == nullptr)
    {
        auto fileName = path.getNameWithoutExtension();

        switch (type)
        {
            case BlobType::Hlsl:
                fileName += ".hlsl";
                break;

            case BlobType::SpirvVertex:
                fileName += ".vs.spirv";
                break;

            case BlobType::SpirvPixel:
                fileName += ".ps.spirv";
                break;

            case BlobType::GlslVertex:
                fileName += ".vs.glsl";
                break;

            case BlobType::GlslPixel:
                fileName += ".ps.glsl";
                break;

            default:
                throw std::exception();
        }

        auto dir = path.getParentPath();
        if (type != BlobType::Hlsl)
            dir.cd("gen");

        auto path = Path::combine(dir, fileName);

        blobs[type] = std::unique_ptr<Blob>(new Blob(path));
    }

    return *blobs[type];
}

const std::string& ShaderBunch::getSourceText(BlobType type)
{
    return getSource(type).asString();
}

Shader* ShaderBunch::getShader(std::string entryPointName)
{
    auto sit = shaders.find(entryPointName);
    if (sit != std::end(shaders))
    {
        return sit->second.get();
    }

    auto eit = entryPoints.find(entryPointName);
    if (eit != std::end(entryPoints))
    {
        auto shader = new Shader(this, eit->second, entryPointName);
        shaders[entryPointName] = std::unique_ptr<Shader>(shader);
        return shaders[entryPointName].get();
    }

    return nullptr;
}
