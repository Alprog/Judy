
#pragma once

#include "Renderer.h"

#include <windows.h>
#include <d3d11.h>

#include "DXShaderResource.h"

class DXSwapChain;

class DXRenderer : public Renderer
{
public:
    std::unordered_map<RenderTarget*, DXSwapChain*> swapChains;

    DXSwapChain* GetSwapChain(RenderTarget* renderTarget);

    DXRenderer();

    std::unordered_map<std::string, DXShaderResource*> shaders;

    virtual void Draw(Mesh* mesh, Material* material, Matrix matrix) override;
    virtual void DrawQuad(Quad* quad) override;
    virtual void Render(Node* scene, RenderTarget* renderTarget) override;

    void Clear(Color color) override;
    void SetTexture(std::string name);
    void SetShader(std::string name);

    ID3D11Device* device;
    ID3D11DeviceContext* deviceContext;

private:
    void InitQuad();

};

