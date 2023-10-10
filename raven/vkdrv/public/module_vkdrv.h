/*
filename:       module_vkdrv.cpp
author:         Raven
date created:   2023-09-27
description:
*/

#pragma once
#include <core/public/core.h>
#include "vkcore.h"
#include "vkinstance.h"
#include "vkdevice.h"


RAVEN_NAMESPACE_BEGIN

class RAVEN_VKDRV_API Module_vkdrv : virtual public Module_vkcore
{
	RAVEN_MODULE_DECLARATION(vkdrv)

public:
	static VkBool32 VkDebugUtilsMessengerCallback(VkDebugUtilsMessageSeverityFlagBitsEXT i_MessageSeverity, VkDebugUtilsMessageTypeFlagsEXT I_MessageType, const VkDebugUtilsMessengerCallbackDataEXT* i_CallbackData, void* i_UserData);

public:
	Module_vkdrv() noexcept;
	virtual ~Module_vkdrv() noexcept;

private:
	RVKInstance* m_pVkInstance = R_NULL;
	RVKDevice* m_pVkDevice = R_NULL;

	VkPhysicalDeviceFeatures2 m_EnablePhysicalDeviceFeatures2{};
	VkPhysicalDeviceVulkan11Features m_EnablePhysicalDeviceVulkan11Features{};
	VkPhysicalDeviceVulkan12Features m_EnablePhysicalDeviceVulkan12Features{};
	VkPhysicalDeviceVulkan13Features m_EnablePhysicalDeviceVulkan13Features{};
	VkPhysicalDeviceSynchronization2FeaturesKHR m_EnablePhysicalDeviceSynchronization2FeaturesKHR{};
	VkPhysicalDeviceAccelerationStructureFeaturesKHR m_EnablePhysicalDeviceAccelerationStructureFeaturesKHR{};
	VkPhysicalDeviceRayTracingPipelineFeaturesKHR m_EnablePhysicalDeviceRayTracingPipelineFeaturesKHR{};
	VkPhysicalDeviceRayQueryFeaturesKHR m_EnablePhysicalDeviceRayQueryFeaturesKHR{};
	VkPhysicalDeviceDescriptorBufferFeaturesEXT m_EnablePhysicalDeviceDescriptorBufferFeaturesEXT{};

	VkPhysicalDeviceFeatures2 m_SupportPhysicalDeviceFeatures2{};
	VkPhysicalDeviceVulkan11Features m_SupportPhysicalDeviceVulkan11Features{};
	VkPhysicalDeviceVulkan12Features m_SupportPhysicalDeviceVulkan12Features{};
	VkPhysicalDeviceVulkan13Features m_SupportPhysicalDeviceVulkan13Features{};
	VkPhysicalDeviceSynchronization2FeaturesKHR m_SupportPhysicalDeviceSynchronization2FeaturesKHR{};
	VkPhysicalDeviceAccelerationStructureFeaturesKHR m_SupportPhysicalDeviceAccelerationStructureFeaturesKHR{};
	VkPhysicalDeviceRayTracingPipelineFeaturesKHR m_SupportPhysicalDeviceRayTracingPipelineFeaturesKHR{};
	VkPhysicalDeviceRayQueryFeaturesKHR m_SupportPhysicalDeviceRayQueryFeaturesKHR{};
	VkPhysicalDeviceDescriptorBufferFeaturesEXT m_SupportPhysicalDeviceDescriptorBufferFeaturesEXT{};
};

RAVEN_NAMESPACE_END