
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

    std::vector<const char*> layers = { "VK_LAYER_LUNARG_standard_validation" };
    CheckLayers(layers);
    instanceInfo.enabledLayerCount = layers.size();
    instanceInfo.ppEnabledLayerNames = &layers[0];

    std::vector<const char*> extensions = { "VK_KHR_win32_surface", "VK_KHR_surface", "VK_EXT_debug_report" };
    CheckExtensions(extensions);
    instanceInfo.enabledExtensionCount = extensions.size();
    instanceInfo.ppEnabledExtensionNames = &extensions[0];


    auto err = vkCreateInstance(&instanceInfo, nullptr, &vulkanInstance);

    if (err)
    {
        exit(err);
    }
}

void FilterNames(std::vector<const char*>& names, std::unordered_set<std::string>& allowNames)
{
    auto it = std::begin(names);
    while (it != std::end(names))
    {
        if (allowNames.find(*it) == std::end(allowNames))
        {
            it = names.erase(it);
            continue;
        }
        it++;
    }
}

void VulkanRenderer::CheckLayers(std::vector<const char*>& names)
{
    std::unordered_set<std::string> set;

    uint32_t count = 0;
    vkEnumerateInstanceLayerProperties(&count, nullptr);
    if (count > 0)
    {
        auto layerProperties = new VkLayerProperties[count];
        vkEnumerateInstanceLayerProperties(&count, layerProperties);
        for (int i = 0; i <= count; i++)
        {
            set.insert(layerProperties[i].layerName);
        }
        delete[] layerProperties;
    }

    FilterNames(names, set);
}

void VulkanRenderer::CheckExtensions(std::vector<const char*>& names)
{
    std::unordered_set<std::string> set;

    uint32_t count = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr);
    if (count > 0)
    {
        auto extensionProperties = new VkExtensionProperties[count];
        vkEnumerateInstanceExtensionProperties(nullptr, &count, extensionProperties);
        for (int i = 0; i <= count; i++)
        {
            set.insert(extensionProperties[i].extensionName);
        }
        delete[] extensionProperties;
    }

    FilterNames(names, set);
}
