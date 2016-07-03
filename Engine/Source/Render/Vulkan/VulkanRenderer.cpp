
#include "VulkanRenderer.h"

VulkanRenderer::VulkanRenderer()
{
    Init();
}

void VulkanRenderer::Render(std::vector<RenderCommand> commands, RenderTarget* target)
{

}

void VulkanRenderer::Draw(RenderCommand renderCommand)
{

}

void VulkanRenderer::Clear(Color color)
{

}

void VulkanRenderer::Init()
{
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pNext = nullptr;
    appInfo.pApplicationName = "Unknown";
    appInfo.pEngineName = "Judy";
    appInfo.engineVersion = 1;
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo instanceInfo;
    instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceInfo.pNext = nullptr;
    instanceInfo.pApplicationInfo = &appInfo;
    instanceInfo.enabledLayerCount = 0;
    instanceInfo.ppEnabledLayerNames = nullptr;
    instanceInfo.enabledExtensionCount = 0;
    instanceInfo.ppEnabledExtensionNames = nullptr;

    auto err = vkCreateInstance(&instanceInfo, nullptr, &vulkanInstance);

    if (err)
    {
        exit(err);
    }
}
