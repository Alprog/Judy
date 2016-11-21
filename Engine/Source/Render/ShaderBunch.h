
#pragma once

#include <Path.h>
#include <Blob.h>
#include <Shader.h>
#include <memory>
#include <unordered_map>

class ShaderBunch
{  
public:
    enum BlobType
    {
        Hlsl,
        SpirvVertex,
        SpirvPixel,
        GlslVertex,
        GlslPixel,
        Count
    };

public:
    ShaderBunch(Path path);

    const std::unordered_map<std::string, ShaderType>& getEntryPoints();
    const Blob& getSource(BlobType type);
    const std::string& getSourceText(BlobType type);

    Shader* getShader(std::string entryPoint);

private:
    Path path;
    std::unique_ptr<Blob> blobs[BlobType::Count];
    std::unordered_map<std::string, ShaderType> entryPoints;

    std::unordered_map<std::string, std::unique_ptr<Shader>> shaders;
};
