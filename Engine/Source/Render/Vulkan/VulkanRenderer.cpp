
#include "VulkanRenderer.h"
#include <cassert>

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

VKAPI_ATTR VkBool32 VKAPI_CALL
DebugCallback(VkFlags msgFlags, VkDebugReportObjectTypeEXT objType, uint64_t srcObject, size_t location,
              int32_t msgCode, const char* pLayerPrefix, const char* pMsg, void* pUserData)
{
    return false;
}

void VulkanRenderer::Init()
{
    InitInstance();
    InitDevice();
    InitSwapChain();
}

template <typename T>
void VulkanRenderer::GetInstanceProcAddr(T& funcPointer, const char* funcName)
{
    funcPointer = (T)vkGetInstanceProcAddr(vulkanInstance, funcName);
    assert(funcPointer);
}

void VulkanRenderer::InitInstance()
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

    GetInstanceProcAddr(regDebugExt, "vkCreateDebugReportCallbackEXT");
    GetInstanceProcAddr(unregDebugExt, "vkDestroyDebugReportCallbackEXT");
    GetInstanceProcAddr(getPhysicalDeviceSurfaceFormats, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR");

    //GetInstanceProcAddr(getPhysicalDeviceSurfaceFormats, vulkanInstance);

    VkDebugReportCallbackCreateInfoEXT debugInfo;
    debugInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
    debugInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
    debugInfo.pfnCallback = DebugCallback;
    debugInfo.pUserData = nullptr;
    debugInfo.pNext = nullptr;
    err = regDebugExt(vulkanInstance, &debugInfo, nullptr, &debugExtension);

    if (err)
    {
        exit(err);
    }
}

void VulkanRenderer::InitSurface()
{
    VkWin32SurfaceCreateInfoKHR surfaceInfo = {};
    surfaceInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    surfaceInfo.pNext = nullptr;
    surfaceInfo.flags = 0;
    //surfaceInfo.hinstance = demo->connection;
    //surfaceInfo.hwnd = demo->window;

    auto err = vkCreateWin32SurfaceKHR(vulkanInstance, &surfaceInfo, nullptr, &surface);
    assert(!err);
}

void VulkanRenderer::InitDevice()
{
    uint32_t count = 0;
    vkEnumeratePhysicalDevices(vulkanInstance, &count, NULL);

    if (count > 0)
    {
        VkPhysicalDevice* physicalDevices = new VkPhysicalDevice[count];
        vkEnumeratePhysicalDevices(vulkanInstance, &count, physicalDevices);
        gpu = physicalDevices[0];
        //delete[] physicalDevices;
    }

    uint32_t queueFamilyIndex = 0; // hardcoded

    VkDeviceQueueCreateInfo queueInfo = {};
    queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueInfo.queueFamilyIndex = queueFamilyIndex;
    queueInfo.queueCount = 1;
    float priorities[] = { 0.0f };
    queueInfo.pQueuePriorities = priorities;

    VkDeviceCreateInfo deviceInfo = {};
    deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceInfo.pNext = nullptr;
    deviceInfo.queueCreateInfoCount = 1;
    deviceInfo.pQueueCreateInfos = &queueInfo;

    std::vector<const char*> layers = { "VK_LAYER_LUNARG_standard_validation" };
    deviceInfo.enabledLayerCount = layers.size();
    deviceInfo.ppEnabledLayerNames = &layers[0];

    std::vector<const char*> extensions = { "VK_KHR_swapchain" };
    deviceInfo.enabledExtensionCount = extensions.size();
    deviceInfo.ppEnabledExtensionNames = &extensions[0];

    VkPhysicalDeviceFeatures features = {};
    features.shaderClipDistance = VK_TRUE;
    deviceInfo.pEnabledFeatures = &features;

    auto result = vkCreateDevice(gpu, &deviceInfo, nullptr, &device);
    if (result)
    {
        exit(0);
    }
}

void VulkanRenderer::InitSwapChain()
{
    uint32_t count;
    auto err = getPhysicalDeviceSurfaceFormats(gpu, surface, &count, nullptr);
    assert(!err && count > 0);
    VkSurfaceFormatKHR* formats = new VkSurfaceFormatKHR[count];
    err = getPhysicalDeviceSurfaceFormats(gpu, surface, &count, formats);

    VkFormat format = formats[0].format;
    VkColorSpaceKHR colorSpace = formats[0].colorSpace;
    if (format == VK_FORMAT_UNDEFINED)
    {
        format = VK_FORMAT_B8G8R8A8_UNORM;
    }

}

void VulkanRenderer::Destroy()
{
    unregDebugExt(vulkanInstance, debugExtension, nullptr);
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
