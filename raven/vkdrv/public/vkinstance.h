/*
filename:       vkinstance.cpp
author:         Raven
date created:   2023-09-06
description:
*/
#pragma once

#include "vkcore.h"

RAVEN_NAMESPACE_BEGIN

class RVKInstance {
public:
	// THE CORE FUNCTIONS
	RAVEN_VULKANFUNCTION_DECL(vkDestroyInstance);									// VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkEnumeratePhysicalDeviceGroups);                     // VK_VERSION_1_1
	RAVEN_VULKANFUNCTION_DECL(vkEnumeratePhysicalDevices);                          // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkEnumerateDeviceExtensionProperties);                // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkGetPhysicalDeviceFeatures2);                        // VK_VERSION_1_1
	RAVEN_VULKANFUNCTION_DECL(vkGetPhysicalDeviceProperties2);                      // VK_VERSION_1_1
	RAVEN_VULKANFUNCTION_DECL(vkGetPhysicalDeviceQueueFamilyProperties2);           // VK_VERSION_1_1
	RAVEN_VULKANFUNCTION_DECL(vkCreateDevice);                                      // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkDestroyDevice);                                     // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkDestroySurfaceKHR);                                 // VK_KHR_surface
	RAVEN_VULKANFUNCTION_DECL(vkGetPhysicalDeviceSurfaceSupportKHR);                // VK_KHR_surface
	RAVEN_VULKANFUNCTION_DECL(vkGetPhysicalDeviceSurfaceCapabilitiesKHR);           // VK_KHR_surface
	RAVEN_VULKANFUNCTION_DECL(vkGetPhysicalDeviceSurfaceFormatsKHR);                // VK_KHR_surface
	RAVEN_VULKANFUNCTION_DECL(vkGetPhysicalDeviceSurfacePresentModesKHR);           // VK_KHR_surface
	RAVEN_VULKANFUNCTION_DECL(vkGetPhysicalDeviceFormatProperties2);                // VK_VERSION_1_1

	RAVEN_VULKANFUNCTION_DECL(vkCreateWin32SurfaceKHR);                             // VK_KHR_win32_surface
	RAVEN_VULKANFUNCTION_DECL(vkGetPhysicalDeviceWin32PresentationSupportKHR);      // VK_KHR_win32_surface

#if RAVEN_VK_EXT_debug_utils
	RAVEN_VULKANFUNCTION_DECL(vkCreateDebugUtilsMessengerEXT);                       // VK_EXT_debug_utils
	RAVEN_VULKANFUNCTION_DECL(vkDestroyDebugUtilsMessengerEXT);                      // VK_EXT_debug_utils
#endif

public:
	RVKInstance(const RVKInstance&) = delete;
	RVKInstance(RVKInstance&&) = delete;
	RVKInstance& operator=(const RVKInstance&) = delete;
	RVKInstance& operator=(RVKInstance&&) = delete;

	RVKInstance() noexcept;
	RVKInstance(const VkInstanceCreateInfo& i_CreateInfo, Bool i_Debug, const VkDebugUtilsMessengerCreateInfoEXT& i_DebugUtilsMessengerCreateInfo) noexcept;
	~RVKInstance() noexcept;

	Bool isCreated() const noexcept;
	void create(const VkInstanceCreateInfo& i_CreateInfo, Bool i_Debug, const VkDebugUtilsMessengerCreateInfoEXT& i_DebugUtilsMessengerCreateInfo) noexcept;
	void destroy() noexcept;
	VkInstance handle() const noexcept;
	VkAllocationCallbacks* allocatorVK() noexcept;

	RVKInstance(U32 i_ApiVer, const std::string& i_AppName, U32 i_AppVer, std::string& i_EngineName, U32 i_EngineVer, const std::vector<const char*>& i_Extensions, const std::vector<const char*>& i_Layers, Bool i_bDebug, PFN_vkDebugUtilsMessengerCallbackEXT i_pDebugCallback) noexcept;
	void create(U32 i_ApiVer, const std::string& i_AppName, U32 i_AppVer, std::string& i_EngineName, U32 i_EngineVer, const std::vector<const char*>& i_Extensions, const std::vector<const char*>& i_Layers, Bool i_bDebug, PFN_vkDebugUtilsMessengerCallbackEXT i_pDebugCallback) noexcept;

	Uint getPhysicalDeviceGroupCount() const noexcept;
	const VkPhysicalDeviceGroupProperties* getPhysicalDeviceGroupProperties(Uint i_Index) const noexcept;

	Uint getPhysicalDeviceCount() const noexcept;
	VkPhysicalDevice getPhysicalDevice(Uint i_Index) const noexcept;

	void getPhysicalDeviceProperties(Uint i_Index, VkPhysicalDeviceProperties& o_Props) const noexcept;
	void getPhysicalDeviceProperties(Uint i_Index, VkPhysicalDeviceProperties2* o_pProps) const noexcept;
	void getPhysicalDeviceProperties(Uint i_Index, VkPhysicalDeviceVulkan11Properties& o_Props) const noexcept;
	void getPhysicalDeviceProperties(Uint i_Index, VkPhysicalDeviceVulkan12Properties& o_Props) const noexcept;
	void getPhysicalDeviceProperties(Uint i_Index, VkPhysicalDeviceVulkan13Properties& o_Props) const noexcept;

	Uint getPhysicalDeviceQueueFamilyCount(Uint i_Index) const noexcept;
	Uint getPhysicalDeviceQueueFamilyProperties(Uint i_pdidx, VkQueueFamilyProperties2* o_pProps, Uint i_BuffSize) const noexcept;
	std::vector<VkQueueFamilyProperties2> getPhysicalDeviceQueueFamilyProperties(Uint i_pdidx) const noexcept;

	Uint getPhysicalDeviceExtensionCount(Uint i_Index, const Char* i_pLayerName) const noexcept;
	Uint getPhysicalDeviceExtensionProperties(Uint i_pdidx, const Char* i_pLayerName, VkExtensionProperties* o_pProps, Uint i_BuffSize) const noexcept;
	std::vector<VkExtensionProperties> getPhysicalDeviceExtensionProperties(Uint i_pdidx, const Char* i_pLayerName) const noexcept;

	void getPhysicalDeviceFeatures(Uint i_Index, VkPhysicalDeviceFeatures2* o_pFeatures) const noexcept;
	void getPhysicalDeviceFeatures(Uint i_Index, VkPhysicalDeviceFeatures& o_pFeatures) const noexcept;
	void getPhysicalDeviceFeatures(Uint i_Index, VkPhysicalDeviceVulkan11Features& o_pFeatures) const noexcept;
	void getPhysicalDeviceFeatures(Uint i_Index, VkPhysicalDeviceVulkan12Features& o_pFeatures) const noexcept;
	void getPhysicalDeviceFeatures(Uint i_Index, VkPhysicalDeviceVulkan13Features& o_pFeatures) const noexcept;

private:
	void updatePhysicalDeviceGroupInfo() noexcept;
	void updatePhysicalDeviceInfo() noexcept;

private:
	VkInstanceCreateInfo				m_CreateInfo;
	Bool								m_bDebugMode;
	VkDebugUtilsMessengerCreateInfoEXT	m_DebugUtilsMessengerCreateInfo;
	VkDebugUtilsMessengerEXT			m_hDebugUtilsMessenger;
	VkInstance							m_hInstance;

	std::vector<VkPhysicalDeviceGroupProperties> m_PhysicalDeviceGroupProperties;
	std::vector<VkPhysicalDevice>		m_PhysicalDevices;
};

class RVKInstanceChild
{
public:
	RVKInstanceChild(RVKInstance* i_pVKInstance) noexcept
		: m_pInstance(i_pVKInstance)
	{

	}

	virtual ~RVKInstanceChild() noexcept
	{

	}

	const RVKInstance& instance() const noexcept
	{
		return *m_pInstance;
	}

	RVKInstance& instance() noexcept
	{
		return *m_pInstance;
	}

	const RVKInstance* instancePtr() const noexcept
	{
		return m_pInstance;
	}

	RVKInstance* instancePtr() noexcept
	{
		return m_pInstance;
	}

	virtual VkAllocationCallbacks* allocatorVK() noexcept
	{
		return m_pInstance->allocatorVK();
	}

private:
	RVKInstance* m_pInstance;

};

RAVEN_NAMESPACE_END