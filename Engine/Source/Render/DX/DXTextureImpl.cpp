
#include "DXTextureImpl.h"
#include "DXRenderer.h"

#include "d3dx12.h"
#include "Images.h"
#include "../Texture.h"
#include "DXDescriptorHeap.h"

static const UINT TexturePixelSize = 4;

Impl<Texture, RendererType::DX>::Impl(DXRenderer* renderer, Texture* resource)
{
    auto image = Images::LoadPng(resource->name);

    auto device = renderer->GetDevice();
    auto commandList = renderer->GetCommandList();
    auto commandAllocator = renderer->GetCommandAllocator();
    auto commandQueue = renderer->GetCommandQueue();

    D3D12_RESOURCE_DESC textureDesc = {};
    textureDesc.MipLevels = 1;
    textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    textureDesc.Width = image->width;
    textureDesc.Height = image->height;
    textureDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
    textureDesc.DepthOrArraySize = 1;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.SampleDesc.Quality = 0;
    textureDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;

    device->CreateCommittedResource(
        &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
        D3D12_HEAP_FLAG_NONE,
        &textureDesc,
        D3D12_RESOURCE_STATE_COPY_DEST,
        nullptr,
        IID_PPV_ARGS(&texture)) MUST;

    const UINT64 uploadBufferSize = GetRequiredIntermediateSize(texture.Get(), 0, 1);

    ComPtr<ID3D12Resource> textureUploadHeap;

    device->CreateCommittedResource(
        &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
        D3D12_HEAP_FLAG_NONE,
        &CD3DX12_RESOURCE_DESC::Buffer(uploadBufferSize),
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&textureUploadHeap)) MUST;

    std::vector<UINT8> data = GenerateChessboard();

    D3D12_SUBRESOURCE_DATA textureData = {};
    textureData.pData = image->data;
    textureData.RowPitch = image->width * TexturePixelSize;
    textureData.SlicePitch = textureData.RowPitch * image->height;

    commandList->Reset(commandAllocator, nullptr);
    UpdateSubresources(commandList, texture.Get(), textureUploadHeap.Get(), 0, 0, 1, &textureData);
    commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(texture.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE));
    commandList->Close();
    ID3D12CommandList* ppCommandLists[] = { commandList };
    commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    srvDesc.Format = textureDesc.Format;
    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = 1;

    descriptorHandle = renderer->GetSrvCbvHeap()->GetNextHandle();
    device->CreateShaderResourceView(texture.Get(), &srvDesc, descriptorHandle.GetCPU());

    static_cast<DXRenderer*>(renderer)->WaitForPreviousFrame();

    delete image;
}

std::vector<UINT8> Impl<Texture, RendererType::DX>::GenerateChessboard()
{
    const UINT rowPitch = 256 * TexturePixelSize;
    const UINT cellPitch = rowPitch >> 3;		// The width of a cell in the checkboard texture.
    const UINT cellHeight = 256 >> 3;	// The height of a cell in the checkerboard texture.
    const UINT textureSize = rowPitch * 256;

    std::vector<UINT8> data(textureSize);
    UINT8* pData = &data[0];

    for (UINT n = 0; n < textureSize; n += TexturePixelSize)
    {
        UINT x = n % rowPitch;
        UINT y = n / rowPitch;
        UINT i = x / cellPitch;
        UINT j = y / cellHeight;

        if (i % 2 == j % 2)
        {
            pData[n] = 0x00;		// R
            pData[n + 1] = 0x00;	// G
            pData[n + 2] = 0x00;	// B
            pData[n + 3] = 0xff;	// A
        }
        else
        {
            pData[n] = 0xff;		// R
            pData[n + 1] = 0xff;	// G
            pData[n + 2] = 0xff;	// B
            pData[n + 3] = 0xff;	// A
        }
    }

    return data;
}
