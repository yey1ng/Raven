/*
filename:       vkinstance.cpp
author:         Raven
date created:   2023-09-06
description:
*/

#include <vkdrv/public/vkinstance.h>

RAVEN_NAMESPACE_BEGIN

RVKInstance::RVKInstance() noexcept
	: m_hInstance(VK_NULL_HANDLE),
	m_CreateInfo(),
	m_bDebugMode(R_FALSE),
	m_DebugUtilsMessengerCreateInfo(),
	m_hDebugUtilsMessenger(VK_NULL_HANDLE),
	m_PhysicalDeviceGroupProperties(),
	m_PhysicalDevices()
{
}

RVKInstance::RVKInstance(const VkInstanceCreateInfo& i_CreateInfo, Bool i_bDebug, const VkDebugUtilsMessengerCreateInfoEXT& i_DebugUtilsMessengerCreateInfo) noexcept
	: m_hInstance(VK_NULL_HANDLE) {
	create(i_CreateInfo, i_bDebug, i_DebugUtilsMessengerCreateInfo);
}

RVKInstance::~RVKInstance() noexcept {
	if (isCreated())
		destroy();
}

Bool RVKInstance::isCreated() const noexcept {
	return m_hInstance != VK_NULL_HANDLE;
}

void RVKInstance::create(const VkInstanceCreateInfo& i_CreateInfo, Bool i_bDebug, const VkDebugUtilsMessengerCreateInfoEXT& i_DebugUtilsMessengerCreateInfo) noexcept {
	if (isCreated())
		R_LOG_ERROR("VkInstance is Created");

	VkResult l_Result = RAVEN_MODULE(vkcore).rvkCreateInstance(&i_CreateInfo, allocatorVK(), &m_hInstance);
	if (l_Result != VK_SUCCESS)
		R_LOG_ERROR("VkInstance Creation failed!");

	m_CreateInfo = i_CreateInfo;
	m_bDebugMode = i_bDebug;
	m_DebugUtilsMessengerCreateInfo = i_DebugUtilsMessengerCreateInfo;

	// THE CORE FUNCTIONS
	RAVEN_VULKANFUNCTION_INSTANCE(vkDestroyInstance, m_hInstance);										// VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_INSTANCE(vkEnumeratePhysicalDeviceGroups, m_hInstance);						// VK_VERSION_1_1
	RAVEN_VULKANFUNCTION_INSTANCE(vkEnumeratePhysicalDevices, m_hInstance);								// VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_INSTANCE(vkEnumerateDeviceExtensionProperties, m_hInstance);					// VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_INSTANCE(vkGetPhysicalDeviceFeatures2, m_hInstance);							// VK_VERSION_1_1
	RAVEN_VULKANFUNCTION_INSTANCE(vkGetPhysicalDeviceProperties2, m_hInstance);							// VK_VERSION_1_1
	RAVEN_VULKANFUNCTION_INSTANCE(vkGetPhysicalDeviceQueueFamilyProperties2, m_hInstance);				// VK_VERSION_1_1
	RAVEN_VULKANFUNCTION_INSTANCE(vkCreateDevice, m_hInstance);											// VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_INSTANCE(vkDestroyDevice, m_hInstance);										// VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_INSTANCE(vkDestroySurfaceKHR, m_hInstance);									// VK_KHR_surface
	RAVEN_VULKANFUNCTION_INSTANCE(vkGetPhysicalDeviceSurfaceSupportKHR, m_hInstance);					// VK_KHR_surface
	RAVEN_VULKANFUNCTION_INSTANCE(vkGetPhysicalDeviceSurfaceCapabilitiesKHR, m_hInstance);				// VK_KHR_surface
	RAVEN_VULKANFUNCTION_INSTANCE(vkGetPhysicalDeviceSurfaceFormatsKHR, m_hInstance);					// VK_KHR_surface
	RAVEN_VULKANFUNCTION_INSTANCE(vkGetPhysicalDeviceSurfacePresentModesKHR, m_hInstance);				// VK_KHR_surface
	RAVEN_VULKANFUNCTION_INSTANCE(vkGetPhysicalDeviceFormatProperties2, m_hInstance);					// VK_VERSION_1_1

	RAVEN_VULKANFUNCTION_INSTANCE(vkCreateWin32SurfaceKHR, m_hInstance);								// VK_KHR_win32_surface
	RAVEN_VULKANFUNCTION_INSTANCE(vkGetPhysicalDeviceWin32PresentationSupportKHR, m_hInstance);			// VK_KHR_win32_surface

#if RAVEN_VK_EXT_debug_utils
	RAVEN_VULKANFUNCTION_INSTANCE(vkCreateDebugUtilsMessengerEXT, m_hInstance);							// VK_EXT_debug_utils
	RAVEN_VULKANFUNCTION_INSTANCE(vkDestroyDebugUtilsMessengerEXT, m_hInstance);						// VK_EXT_debug_utils
#endif

	updatePhysicalDeviceGroupInfo();
	updatePhysicalDeviceInfo();

	m_hDebugUtilsMessenger = VK_NULL_HANDLE;
	if (m_bDebugMode) {
#if RAVEN_VK_EXT_debug_utils
		if (m_DebugUtilsMessengerCreateInfo.pfnUserCallback) {
			VkResult l_Result = rvkCreateDebugUtilsMessengerEXT(m_hInstance, &m_DebugUtilsMessengerCreateInfo, VK_NULL_HANDLE, &m_hDebugUtilsMessenger);
			if (l_Result != VK_SUCCESS) {
				R_LOG_WARNING("DebugUtilsMessenger extension create failed!");
			}
		}
#endif
	}

	R_LOG_INFO("VKInstance create success");
}

void RVKInstance::destroy() noexcept
{
	if (!isCreated())
		R_LOG_ERROR("VkInstance isn't Created");

#if RAVEN_VK_EXT_debug_utils
	if (m_hDebugUtilsMessenger != VK_NULL_HANDLE)
		rvkDestroyDebugUtilsMessengerEXT(m_hInstance, m_hDebugUtilsMessenger, allocatorVK());
#endif

	rvkDestroyInstance(m_hInstance, allocatorVK());

	R_LOG_INFO("VKInstance Destroy");
}

VkInstance RVKInstance::handle() const noexcept
{
	return m_hInstance;
}

VkAllocationCallbacks* RVKInstance::allocatorVK() noexcept {
	return RAVEN_MODULE(vkcore).getVkAllocator();
}


RVKInstance::RVKInstance(U32 i_ApiVer, const std::string& i_AppName, U32 i_AppVer, std::string& i_EngineName, U32 i_EngineVer, const std::vector<const char*>& i_Extensions, const std::vector<const char*>& i_Layers, Bool i_bDebug, PFN_vkDebugUtilsMessengerCallbackEXT i_pDebugCallback) noexcept
	: m_hInstance(VK_NULL_HANDLE) {
	create(i_ApiVer, i_AppName, i_AppVer, i_EngineName, i_EngineVer, i_Extensions, i_Layers, i_bDebug, i_pDebugCallback);
}

void RVKInstance::create(U32 i_ApiVer, const std::string& i_AppName, U32 i_AppVer, std::string& i_EngineName, U32 i_EngineVer, const std::vector<const char*>& i_Extensions, const std::vector<const char*>& i_Layers, Bool i_bDebug, PFN_vkDebugUtilsMessengerCallbackEXT i_pDebugCallback) noexcept {

	VkInstanceCreateInfo l_InstanceCreateInfo{};
	VkDebugUtilsMessengerCreateInfoEXT l_DebugUtilsMessengerCreateInfo;

	VkApplicationInfo l_AppInfo{};
	l_AppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	l_AppInfo.pApplicationName = i_AppName.c_str();
	l_AppInfo.applicationVersion = i_AppVer;
	l_AppInfo.pEngineName = i_EngineName.c_str();
	l_AppInfo.engineVersion = i_EngineVer;
	l_AppInfo.apiVersion = i_ApiVer;

	l_InstanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	l_InstanceCreateInfo.pApplicationInfo = &l_AppInfo;

	std::vector<const char*> l_Extensions = i_Extensions;
	std::vector<const char*> l_Layers = i_Layers;

#if RAVEN_VK_KHR_surface
	l_Extensions.push_back("VK_KHR_surface");
#endif

#if RAVEN_VK_KHR_win32_surface
	l_Extensions.push_back("VK_KHR_win32_surface");
#endif

#if RAVEN_VK_LAYER_KHRONOS_synchronization2
	l_Layers.push_back("VK_LAYER_KHRONOS_synchronization2");
#endif

	if (i_bDebug)
	{
#if RAVEN_VK_EXT_debug_utils
		if (i_pDebugCallback)
		{
			l_DebugUtilsMessengerCreateInfo = {};
			l_DebugUtilsMessengerCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
			l_DebugUtilsMessengerCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
				| VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
			l_DebugUtilsMessengerCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
				| VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
			l_DebugUtilsMessengerCreateInfo.pfnUserCallback = i_pDebugCallback;

			l_InstanceCreateInfo.pNext = &l_DebugUtilsMessengerCreateInfo;
		}

		l_Extensions.push_back("VK_EXT_debug_utils");
#endif

#if RAVEN_VK_LAYER_KHRONOS_validation
		l_Layers.push_back("VK_LAYER_KHRONOS_validation");
#endif
	}

	l_InstanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(l_Extensions.size());
	if (l_InstanceCreateInfo.enabledExtensionCount > 0) {
		l_InstanceCreateInfo.ppEnabledExtensionNames = l_Extensions.data();
	}

	l_InstanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(l_Layers.size());
	if (l_InstanceCreateInfo.enabledLayerCount > 0) {
		l_InstanceCreateInfo.ppEnabledLayerNames = l_Layers.data();
	}

	create(l_InstanceCreateInfo, i_bDebug, l_DebugUtilsMessengerCreateInfo);
}

Uint RVKInstance::getPhysicalDeviceGroupCount() const noexcept
{
	return static_cast<Uint>(m_PhysicalDeviceGroupProperties.size());
}

const VkPhysicalDeviceGroupProperties* RVKInstance::getPhysicalDeviceGroupProperties(Uint i_Index) const noexcept
{
	if (i_Index < m_PhysicalDeviceGroupProperties.size())
		return &m_PhysicalDeviceGroupProperties[i_Index];
	return R_NULL;
}

Uint RVKInstance::getPhysicalDeviceCount() const noexcept
{
	return static_cast<Uint>(m_PhysicalDevices.size());
}

VkPhysicalDevice RVKInstance::getPhysicalDevice(Uint i_Index) const noexcept
{
	if (i_Index < m_PhysicalDevices.size())
		return m_PhysicalDevices[i_Index];
	return VK_NULL_HANDLE;
}

void RVKInstance::getPhysicalDeviceProperties(Uint i_Index, VkPhysicalDeviceProperties& o_Props) const noexcept
{
	VkPhysicalDeviceProperties2 l_Props{};
	l_Props.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
	getPhysicalDeviceProperties(i_Index, &l_Props);
	memcpy(&o_Props, &l_Props.properties, sizeof(VkPhysicalDeviceProperties));
}

void RVKInstance::getPhysicalDeviceProperties(Uint i_Index, VkPhysicalDeviceProperties2* o_pProps) const noexcept
{
	if (i_Index >= getPhysicalDeviceCount())
		R_LOG_INFO("Physical Device not found");

	rvkGetPhysicalDeviceProperties2(getPhysicalDevice(i_Index), o_pProps);
}

void RVKInstance::getPhysicalDeviceProperties(Uint i_Index, VkPhysicalDeviceVulkan11Properties& o_Props) const noexcept
{
	VkPhysicalDeviceProperties2 l_Props{};
	l_Props.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
	VkPhysicalDeviceVulkan11Properties l_Vulkan11Props{};
	l_Vulkan11Props.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_PROPERTIES;
	l_Props.pNext = &l_Vulkan11Props;
	getPhysicalDeviceProperties(i_Index, &l_Props);
	memcpy(&o_Props, &l_Props.properties, sizeof(VkPhysicalDeviceProperties));
}

void RVKInstance::getPhysicalDeviceProperties(Uint i_Index, VkPhysicalDeviceVulkan12Properties& o_Props) const noexcept
{
	VkPhysicalDeviceProperties2 l_Props{};
	l_Props.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
	VkPhysicalDeviceVulkan12Properties l_Vulkan12Props{};
	l_Vulkan12Props.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_PROPERTIES;
	l_Props.pNext = &l_Vulkan12Props;
	getPhysicalDeviceProperties(i_Index, &l_Props);
	memcpy(&o_Props, &l_Props.properties, sizeof(VkPhysicalDeviceProperties));
}

void RVKInstance::getPhysicalDeviceProperties(Uint i_Index, VkPhysicalDeviceVulkan13Properties& o_Props) const noexcept
{
	VkPhysicalDeviceProperties2 l_Props{};
	l_Props.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
	VkPhysicalDeviceVulkan13Properties l_Vulkan13Props{};
	l_Vulkan13Props.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_PROPERTIES;
	l_Props.pNext = &l_Vulkan13Props;
	getPhysicalDeviceProperties(i_Index, &l_Props);
	memcpy(&o_Props, &l_Props.properties, sizeof(VkPhysicalDeviceProperties));
}

Uint RVKInstance::getPhysicalDeviceQueueFamilyCount(Uint i_Index) const noexcept
{
	if (i_Index >= getPhysicalDeviceCount())
		return 0;

	U32 l_Count = 0;
	rvkGetPhysicalDeviceQueueFamilyProperties2(getPhysicalDevice(i_Index), &l_Count, R_NULL);
	return l_Count;
}

Uint RVKInstance::getPhysicalDeviceQueueFamilyProperties(Uint i_pdidx, VkQueueFamilyProperties2* o_pProps, Uint i_BuffSize) const noexcept
{
	R_LOG_FATAL(i_pdidx < getPhysicalDeviceCount(), "Physical Device not found")
		if (o_pProps && i_BuffSize > 0)
		{
			U32 l_Count = (U32)i_BuffSize;
			rvkGetPhysicalDeviceQueueFamilyProperties2(getPhysicalDevice(i_pdidx), &l_Count, o_pProps);
			return l_Count;
		}
	return getPhysicalDeviceQueueFamilyCount(i_pdidx);
}

std::vector<VkQueueFamilyProperties2> RVKInstance::getPhysicalDeviceQueueFamilyProperties(Uint i_pdidx) const noexcept
{
	R_LOG_FATAL(i_pdidx < getPhysicalDeviceCount(), "Physical Device not found")
		Uint l_Count = getPhysicalDeviceQueueFamilyCount(i_pdidx);
	std::vector<VkQueueFamilyProperties2> l_Props(static_cast<U32>(l_Count));
	for (Uint i = 0; i < l_Count; ++i)
	{
		l_Props[i].sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2;
	}
	Uint l_CountVerify = getPhysicalDeviceQueueFamilyProperties(i_pdidx, l_Props.data(), l_Count);
	R_LOG_FATAL(l_Count == l_CountVerify, "Physical Device not found")
		return l_Props;
}

Uint RVKInstance::getPhysicalDeviceExtensionCount(Uint i_Index, const Char* i_pLayerName) const noexcept
{
	if (i_Index >= getPhysicalDeviceCount())
		return 0;

	U32 l_Count = 0;
	VkResult l_vkResult = rvkEnumerateDeviceExtensionProperties(getPhysicalDevice(i_Index), i_pLayerName, &l_Count, R_NULL);
	if (l_vkResult == VK_SUCCESS)
		return l_Count;
	return 0;
}

Uint RVKInstance::getPhysicalDeviceExtensionProperties(Uint i_pdidx, const Char* i_pLayerName, VkExtensionProperties* o_pProps, Uint i_BuffSize) const noexcept
{
	R_LOG_FATAL(i_pdidx < getPhysicalDeviceCount(), "Physical Device not found")
		if (o_pProps && i_BuffSize > 0)
		{
			U32 l_Count = (U32)i_BuffSize;
			VkResult l_vkResult = rvkEnumerateDeviceExtensionProperties(getPhysicalDevice(i_pdidx), i_pLayerName, &l_Count, o_pProps);
			return l_Count;
		}
	return getPhysicalDeviceExtensionCount(i_pdidx, i_pLayerName);
}

std::vector<VkExtensionProperties> RVKInstance::getPhysicalDeviceExtensionProperties(Uint i_pdidx, const Char* i_pLayerName) const noexcept
{
	R_LOG_FATAL(i_pdidx < getPhysicalDeviceCount(), "Physical Device not found")
		Uint l_Count = getPhysicalDeviceExtensionCount(i_pdidx, i_pLayerName);
	std::vector<VkExtensionProperties> l_Props((U32)l_Count);
	Uint l_CountVerify = getPhysicalDeviceExtensionProperties(i_pdidx, i_pLayerName, l_Props.data(), l_Count);
	return l_Props;
}

void RVKInstance::getPhysicalDeviceFeatures(Uint i_Index, VkPhysicalDeviceFeatures2* o_pFeatures) const noexcept
{
	R_LOG_FATAL(i_Index < getPhysicalDeviceCount(), "Physical Device not found")

		rvkGetPhysicalDeviceFeatures2(getPhysicalDevice(i_Index), o_pFeatures);
}

void RVKInstance::getPhysicalDeviceFeatures(Uint i_Index, VkPhysicalDeviceFeatures& o_pFeatures) const noexcept
{
	VkPhysicalDeviceFeatures2 l_Features{};
	l_Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
	getPhysicalDeviceFeatures(i_Index, &l_Features);
	memcpy(&o_pFeatures, &l_Features.features, sizeof(VkPhysicalDeviceFeatures));
}

void RVKInstance::getPhysicalDeviceFeatures(Uint i_Index, VkPhysicalDeviceVulkan11Features& o_pFeatures) const noexcept
{
	VkPhysicalDeviceFeatures2 l_Features{};
	l_Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
	VkPhysicalDeviceVulkan11Features l_Vulkan11Features{};
	l_Vulkan11Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES;
	l_Features.pNext = &l_Vulkan11Features;
	getPhysicalDeviceFeatures(i_Index, &l_Features);
	memcpy(&o_pFeatures, &l_Features.features, sizeof(VkPhysicalDeviceVulkan11Features));
}

void RVKInstance::getPhysicalDeviceFeatures(Uint i_Index, VkPhysicalDeviceVulkan12Features& o_pFeatures) const noexcept
{
	VkPhysicalDeviceFeatures2 l_Features{};
	l_Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
	VkPhysicalDeviceVulkan12Features l_Vulkan12Features{};
	l_Vulkan12Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
	l_Features.pNext = &l_Vulkan12Features;
	getPhysicalDeviceFeatures(i_Index, &l_Features);
	memcpy(&o_pFeatures, &l_Features.features, sizeof(VkPhysicalDeviceVulkan12Features));
}

void RVKInstance::getPhysicalDeviceFeatures(Uint i_Index, VkPhysicalDeviceVulkan13Features& o_pFeatures) const noexcept
{
	VkPhysicalDeviceFeatures2 l_Features{};
	l_Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
	VkPhysicalDeviceVulkan13Features l_Vulkan13Features{};
	l_Vulkan13Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;
	l_Features.pNext = &l_Vulkan13Features;
	getPhysicalDeviceFeatures(i_Index, &l_Features);
	memcpy(&o_pFeatures, &l_Features.features, sizeof(VkPhysicalDeviceVulkan13Features));
}

void RVKInstance::updatePhysicalDeviceGroupInfo() noexcept
{
	U32 l_GroupCount = 0;
	VkResult l_Result = rvkEnumeratePhysicalDeviceGroups(m_hInstance, &l_GroupCount, R_NULL);

	m_PhysicalDeviceGroupProperties.resize(l_GroupCount);
	for (auto& l_PhysicalDeviceGroupProp : m_PhysicalDeviceGroupProperties)
		l_PhysicalDeviceGroupProp.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GROUP_PROPERTIES;
	l_Result = rvkEnumeratePhysicalDeviceGroups(m_hInstance, &l_GroupCount, m_PhysicalDeviceGroupProperties.data());
}

void RVKInstance::updatePhysicalDeviceInfo() noexcept
{
	U32 l_Count = 0;
	VkResult l_Result = rvkEnumeratePhysicalDevices(m_hInstance, &l_Count, R_NULL);

	m_PhysicalDevices.resize(l_Count);
	l_Result = rvkEnumeratePhysicalDevices(m_hInstance, &l_Count, m_PhysicalDevices.data());
}

RAVEN_NAMESPACE_END