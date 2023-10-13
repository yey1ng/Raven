/*
filename:       vkdrv.cpp
author:         Raven
date created:   2023-09-27
description:
*/

#include <vkdrv/public/module_vkdrv.h>

RAVEN_NAMESPACE_BEGIN

RAVEN_MODULE_IMPLEMENTATION(vkdrv)

VkBool32 Module_vkdrv::VkDebugUtilsMessengerCallback(VkDebugUtilsMessageSeverityFlagBitsEXT i_MessageSeverity, VkDebugUtilsMessageTypeFlagsEXT I_MessageType, const VkDebugUtilsMessengerCallbackDataEXT* i_CallbackData, void* i_UserData)
{
	if (i_MessageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT)
		R_LOG_INFO("[Vulkan] %d - %s: %s", i_CallbackData->messageIdNumber, i_CallbackData->pMessageIdName, i_CallbackData->pMessage);
	if (i_MessageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
		R_LOG_INFO("[Vulkan] %d - %s: %s", i_CallbackData->messageIdNumber, i_CallbackData->pMessageIdName, i_CallbackData->pMessage);
	if (i_MessageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
		R_LOG_WARNING("[Vulkan] %d - %s: %s", i_CallbackData->messageIdNumber, i_CallbackData->pMessageIdName, i_CallbackData->pMessage);
	if (i_MessageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
		R_LOG_ERROR("[Vulkan] %d - %s: %s", i_CallbackData->messageIdNumber, i_CallbackData->pMessageIdName, i_CallbackData->pMessage);

	// Always return VK_FALSE, VK_TRUE is reserved for future use(Vulkan doc).
	return VK_FALSE;
}

void addExtensionIfSupport(const std::set<const char*>& i_SupportExtensions, std::vector<const char*>& l_EnbaleExtensions, const std::string& i_Extension)
{
	if (i_SupportExtensions.find(i_Extension.c_str()) != i_SupportExtensions.end())
	{
		l_EnbaleExtensions.emplace_back(i_Extension.c_str());
	}
	else
	{
		R_LOG_ERROR("trying to enable extension (%s), which is not supported by the device.", i_Extension.c_str());
	}
}

void setFeatruesIfSupport(const VkBool32& i_SupportFeatrue, VkBool32& i_EnableFeatrue, const std::string& i_SupportFeatrueStr)
{
	i_EnableFeatrue = VK_TRUE;
	if (i_SupportFeatrue == VK_FALSE)
	{
		i_EnableFeatrue = VK_FALSE;
		R_LOG_WARNING("trying to enable feature (%s), which is not supported by the device.", i_SupportFeatrueStr.c_str());
	}
}

Module_vkdrv::Module_vkdrv() noexcept
{
	//Create VKInstance
	{
		std::vector<const char*> l_Extensions, l_Layers;

		m_pVkInstance = RAVEN_NEW(RVKInstance);
		m_pVkInstance->create(VK_API_VERSION_1_3, std::string("Raven"), 0, std::string("Raven"), 0, l_Extensions, l_Layers, R_TRUE, &VkDebugUtilsMessengerCallback);
	}

	//Create VkDevice
	{
		m_pVkDevice = RAVEN_NEW(RVKDevice)(m_pVkInstance);

		U32 l_PhysicalDeviceIdx = 0;
		std::vector<U32> l_ComputeQueueFamilyIdxs;
		std::vector<U32> l_TransferQueueFamilyIdxs;
		std::vector<U32> l_GraphicsQueueFamilyIdxs;

		std::vector<VkQueueFamilyProperties2> l_QueueFamilyProperties = m_pVkInstance->getPhysicalDeviceQueueFamilyProperties(l_PhysicalDeviceIdx);
		for (U32 i = 0; i < l_QueueFamilyProperties.size(); ++i)
		{
			const VkQueueFamilyProperties2 l_QueueFamilyProperty = l_QueueFamilyProperties[i];

			// Dedicated queue for compute
			// Try to find a queue family index that supports compute but not graphics
			if ((l_QueueFamilyProperty.queueFamilyProperties.queueFlags & VK_QUEUE_COMPUTE_BIT) && (l_QueueFamilyProperty.queueFamilyProperties.queueFlags & VK_QUEUE_GRAPHICS_BIT) == 0)
			{
				l_ComputeQueueFamilyIdxs.emplace_back(i);
			}

			// Dedicated queue for transfer
			// Try to find a queue family index that supports transfer but not graphics and compute
			if ((l_QueueFamilyProperty.queueFamilyProperties.queueFlags & VK_QUEUE_TRANSFER_BIT) && (l_QueueFamilyProperty.queueFamilyProperties.queueFlags & VK_QUEUE_GRAPHICS_BIT) == 0)
			{
				l_TransferQueueFamilyIdxs.emplace_back(i);
			}

			if ((l_QueueFamilyProperty.queueFamilyProperties.queueFlags & VK_QUEUE_GRAPHICS_BIT))
			{
				l_GraphicsQueueFamilyIdxs.emplace_back(i);
			}
		}

		if (l_GraphicsQueueFamilyIdxs.size() == 0)
			R_LOG_ERROR("Not Found Graphics QueueFamily");

		std::vector<VkDeviceQueueCreateInfo> l_DeviceQueueCreateInfos{};
		std::vector<VkQueueAssignment> l_QueueFamilyAssignments;

		// DeviceQueueCreateInfo
		{
			U32 l_ComputeQueueFamilyIdx;
			U32 l_TransferQueueFamilyIdx;
			U32 l_GraphicsQueueFamilyIdx;
			U32 l_PresentQueueFamilyIdx;
			l_GraphicsQueueFamilyIdx = l_GraphicsQueueFamilyIdxs[0];
			l_PresentQueueFamilyIdx = l_GraphicsQueueFamilyIdx;
			if (l_ComputeQueueFamilyIdxs.size() > 0)
				l_ComputeQueueFamilyIdx = l_ComputeQueueFamilyIdxs[0];
			else
				l_ComputeQueueFamilyIdx = l_GraphicsQueueFamilyIdx;
			if (l_TransferQueueFamilyIdxs.size() > 0)
				l_TransferQueueFamilyIdx = l_TransferQueueFamilyIdxs[0];
			else
				l_TransferQueueFamilyIdx = l_GraphicsQueueFamilyIdx;

			l_QueueFamilyAssignments.resize(4);
			l_QueueFamilyAssignments[0].m_QueueFamilyUsage = VK_QUEUEFAMILY_USAGE::COMPUTE_QUEUEFAMILY;
			l_QueueFamilyAssignments[0].m_QueueFamily = l_ComputeQueueFamilyIdx;
			l_QueueFamilyAssignments[0].m_QueueStart = 0;
			l_QueueFamilyAssignments[0].m_QueueCount = 1;
			l_QueueFamilyAssignments[1].m_QueueFamilyUsage = VK_QUEUEFAMILY_USAGE::TRANSFER_QUEUEFAMILY;
			l_QueueFamilyAssignments[1].m_QueueFamily = l_TransferQueueFamilyIdx;
			l_QueueFamilyAssignments[1].m_QueueStart = 0;
			l_QueueFamilyAssignments[1].m_QueueCount = 1;
			l_QueueFamilyAssignments[2].m_QueueFamilyUsage = VK_QUEUEFAMILY_USAGE::GRAPHIC_QUEUEFAMILY;
			l_QueueFamilyAssignments[2].m_QueueFamily = l_GraphicsQueueFamilyIdx;
			l_QueueFamilyAssignments[2].m_QueueStart = 0;
			l_QueueFamilyAssignments[2].m_QueueCount = 1;
			l_QueueFamilyAssignments[3].m_QueueFamilyUsage = VK_QUEUEFAMILY_USAGE::PRESENT_QUEUEFAMILY;
			l_QueueFamilyAssignments[3].m_QueueFamily = l_PresentQueueFamilyIdx;
			l_QueueFamilyAssignments[3].m_QueueStart = 0;
			l_QueueFamilyAssignments[3].m_QueueCount = 1;

			const float l_DefaultQueuePriority(0.0f);
			// If transfer family index differs, we need an additional queue create info for the transfer queue
			if (l_ComputeQueueFamilyIdx != l_GraphicsQueueFamilyIdx)
			{
				VkDeviceQueueCreateInfo l_DeviceQueueCreateInfo{};
				l_DeviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
				l_DeviceQueueCreateInfo.queueFamilyIndex = l_ComputeQueueFamilyIdx;
				l_DeviceQueueCreateInfo.queueCount = 1;
				l_DeviceQueueCreateInfo.pQueuePriorities = &l_DefaultQueuePriority;
				l_DeviceQueueCreateInfos.emplace_back(std::move(l_DeviceQueueCreateInfo));
			}

			if (l_TransferQueueFamilyIdx != l_GraphicsQueueFamilyIdx)
			{
				VkDeviceQueueCreateInfo l_DeviceQueueCreateInfo{};
				l_DeviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
				l_DeviceQueueCreateInfo.queueFamilyIndex = l_TransferQueueFamilyIdx;
				l_DeviceQueueCreateInfo.queueCount = 1;
				l_DeviceQueueCreateInfo.pQueuePriorities = &l_DefaultQueuePriority;
				l_DeviceQueueCreateInfos.emplace_back(std::move(l_DeviceQueueCreateInfo));
			}

			VkDeviceQueueCreateInfo l_DeviceQueueCreateInfo{};
			l_DeviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			l_DeviceQueueCreateInfo.queueFamilyIndex = l_GraphicsQueueFamilyIdx;
			l_DeviceQueueCreateInfo.queueCount = 1;
			l_DeviceQueueCreateInfo.pQueuePriorities = &l_DefaultQueuePriority;
			l_DeviceQueueCreateInfos.emplace_back(std::move(l_DeviceQueueCreateInfo));
		}
		
		// EnableExtension
		std::vector<const char*> l_EnableExtensions{};
		{
			U32 l_MaxExtensionsCount = 0;
			std::vector<VkExtensionProperties> l_Extensions{};
			VkResult l_Result = m_pVkInstance->rvkEnumerateDeviceExtensionProperties(m_pVkInstance->getPhysicalDevice(l_PhysicalDeviceIdx), R_NULL, &l_MaxExtensionsCount, VK_NULL_HANDLE);
			l_Extensions.resize(l_MaxExtensionsCount);
			l_Result = m_pVkInstance->rvkEnumerateDeviceExtensionProperties(m_pVkInstance->getPhysicalDevice(l_PhysicalDeviceIdx), R_NULL, &l_MaxExtensionsCount, l_Extensions.data());

			std::set<const char*> l_SupportExtensions{};
			for (const auto& l_Extension : l_Extensions)
			{
				l_SupportExtensions.emplace(l_Extension.extensionName);
			}

			/*
			  The Vulkan spec states:
				 If the [VK_KHR_portability_subset] extension is included in pProperties of vkEnumerateDeviceExtensionProperties,
				 ppEnabledExtensions must include "VK_KHR_portability_subset"
				 (https://vulkan.lunarg.com/doc/view/1.2.189.0/mac/1.2-extensions/vkspec.html#VUID-VkDeviceCreateInfo-pProperties-04451)
			  */
			addExtensionIfSupport(l_SupportExtensions, l_EnableExtensions, std::string("VK_KHR_portability_subset"));
#if RAVEN_VK_KHR_swapchain
			addExtensionIfSupport(l_SupportExtensions, l_EnableExtensions, std::string("VK_KHR_swapchain"));
#endif
#if RAVEN_VK_KHR_swapchain
			addExtensionIfSupport(l_SupportExtensions, l_EnableExtensions, std::string("VK_KHR_swapchain"));
#endif
#if RAVEN_VK_KHR_synchronization2
			addExtensionIfSupport(l_SupportExtensions, l_EnableExtensions, std::string("VK_KHR_synchronization2"));
#endif
#if RAVEN_VK_KHR_shader_non_semantic_info
			addExtensionIfSupport(l_SupportExtensions, l_EnableExtensions, std::string("VK_KHR_shader_non_semantic_info"));
#endif
#if RAVEN_VK_KHR_ray_tracing_pipeline
			addExtensionIfSupport(l_SupportExtensions, l_EnableExtensions, std::string("VK_KHR_ray_tracing_pipeline"));
			addExtensionIfSupport(l_SupportExtensions, l_EnableExtensions, std::string("VK_KHR_spirv_1_4"));
			addExtensionIfSupport(l_SupportExtensions, l_EnableExtensions, std::string("VK_KHR_shader_float_controls"));
			addExtensionIfSupport(l_SupportExtensions, l_EnableExtensions, std::string("VK_KHR_ray_query"));
#endif
#if RAVEN_VK_KHR_push_descriptor
			addExtensionIfSupport(l_SupportExtensions, l_EnableExtensions, std::string("VK_KHR_push_descriptor"));
#endif
#if RAVEN_VK_EXT_descriptor_buffer
			addExtensionIfSupport(l_SupportExtensions, l_EnableExtensions, std::string("VK_EXT_descriptor_buffer"));
#endif

#if RAVEN_VK_KHR_acceleration_structure
			addExtensionIfSupport(l_SupportExtensions, l_EnableExtensions, std::string("VK_KHR_acceleration_structure"));
			addExtensionIfSupport(l_SupportExtensions, l_EnableExtensions, std::string("VK_KHR_deferred_host_operations"));
			addExtensionIfSupport(l_SupportExtensions, l_EnableExtensions, std::string("VK_EXT_descriptor_indexing"));
#endif
#if RAVEN_VK_KHR_buffer_device_address
			addExtensionIfSupport(l_SupportExtensions, l_EnableExtensions, std::string("VK_KHR_buffer_device_address"));
#endif
#if RAVEN_VK_EXT_descriptor_buffer
			addExtensionIfSupport(l_SupportExtensions, l_EnableExtensions, std::string("VK_EXT_descriptor_buffer"));
#endif
		}
	
		//Enable Features
		{
			m_SupportPhysicalDeviceFeatures2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
			m_SupportPhysicalDeviceVulkan11Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES;
			m_SupportPhysicalDeviceVulkan12Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
			m_SupportPhysicalDeviceVulkan13Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;
			m_SupportPhysicalDeviceSynchronization2FeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SYNCHRONIZATION_2_FEATURES_KHR;
			m_SupportPhysicalDeviceAccelerationStructureFeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR;
			m_SupportPhysicalDeviceRayTracingPipelineFeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR;
			m_SupportPhysicalDeviceRayQueryFeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_QUERY_FEATURES_KHR;
			m_SupportPhysicalDeviceDescriptorBufferFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_BUFFER_FEATURES_EXT;

			m_SupportPhysicalDeviceRayQueryFeaturesKHR.pNext = &m_SupportPhysicalDeviceDescriptorBufferFeaturesEXT;
			m_SupportPhysicalDeviceRayTracingPipelineFeaturesKHR.pNext = &m_SupportPhysicalDeviceRayQueryFeaturesKHR;
			m_SupportPhysicalDeviceAccelerationStructureFeaturesKHR.pNext = &m_SupportPhysicalDeviceRayTracingPipelineFeaturesKHR;
			m_SupportPhysicalDeviceSynchronization2FeaturesKHR.pNext = &m_SupportPhysicalDeviceAccelerationStructureFeaturesKHR;
			m_SupportPhysicalDeviceVulkan13Features.pNext = &m_SupportPhysicalDeviceSynchronization2FeaturesKHR;
			m_SupportPhysicalDeviceVulkan12Features.pNext = &m_SupportPhysicalDeviceVulkan13Features;
			m_SupportPhysicalDeviceVulkan11Features.pNext = &m_SupportPhysicalDeviceVulkan12Features;
			m_SupportPhysicalDeviceFeatures2.pNext = &m_SupportPhysicalDeviceVulkan11Features;

			m_pVkInstance->rvkGetPhysicalDeviceFeatures2(m_pVkInstance->getPhysicalDevice(l_PhysicalDeviceIdx), &m_SupportPhysicalDeviceFeatures2);

			m_EnablePhysicalDeviceFeatures2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
			m_EnablePhysicalDeviceVulkan11Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES;
			m_EnablePhysicalDeviceVulkan12Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
			m_EnablePhysicalDeviceVulkan13Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;
			m_EnablePhysicalDeviceSynchronization2FeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SYNCHRONIZATION_2_FEATURES_KHR;
			m_EnablePhysicalDeviceAccelerationStructureFeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR;
			m_EnablePhysicalDeviceRayTracingPipelineFeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR;
			m_EnablePhysicalDeviceRayQueryFeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_QUERY_FEATURES_KHR;
			m_EnablePhysicalDeviceDescriptorBufferFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_BUFFER_FEATURES_EXT;

			m_EnablePhysicalDeviceRayQueryFeaturesKHR.pNext = &m_EnablePhysicalDeviceDescriptorBufferFeaturesEXT;
			m_EnablePhysicalDeviceRayTracingPipelineFeaturesKHR.pNext = &m_EnablePhysicalDeviceRayQueryFeaturesKHR;
			m_EnablePhysicalDeviceAccelerationStructureFeaturesKHR.pNext = &m_EnablePhysicalDeviceRayTracingPipelineFeaturesKHR;
			m_EnablePhysicalDeviceSynchronization2FeaturesKHR.pNext = &m_EnablePhysicalDeviceAccelerationStructureFeaturesKHR;
			m_EnablePhysicalDeviceVulkan13Features.pNext = &m_EnablePhysicalDeviceSynchronization2FeaturesKHR;
			m_EnablePhysicalDeviceVulkan12Features.pNext = &m_EnablePhysicalDeviceVulkan13Features;
			m_EnablePhysicalDeviceVulkan11Features.pNext = &m_EnablePhysicalDeviceVulkan12Features;
			m_EnablePhysicalDeviceFeatures2.pNext = &m_EnablePhysicalDeviceVulkan11Features;

			setFeatruesIfSupport(m_SupportPhysicalDeviceFeatures2.features.geometryShader, m_EnablePhysicalDeviceFeatures2.features.geometryShader, "VkPhysicalDeviceFeatures.geometryShader");
			setFeatruesIfSupport(m_SupportPhysicalDeviceFeatures2.features.shaderInt16, m_EnablePhysicalDeviceFeatures2.features.shaderInt16, "VkPhysicalDeviceFeatures.shaderInt16");
			setFeatruesIfSupport(m_SupportPhysicalDeviceFeatures2.features.samplerAnisotropy, m_EnablePhysicalDeviceFeatures2.features.samplerAnisotropy, "VkPhysicalDeviceFeatures.samplerAnisotropy");

			setFeatruesIfSupport(m_SupportPhysicalDeviceVulkan12Features.shaderFloat16, m_EnablePhysicalDeviceVulkan12Features.shaderFloat16, "VkPhysicalDeviceVulkan12Features.shaderFloat16");

#if RAVEN_VK_KHR_synchronization2
			setFeatruesIfSupport(m_SupportPhysicalDeviceSynchronization2FeaturesKHR.synchronization2, m_EnablePhysicalDeviceSynchronization2FeaturesKHR.synchronization2, "VkPhysicalDeviceSynchronization2FeaturesKHR.synchronization2");
#endif
#if RAVEN_VK_KHR_buffer_device_address
			setFeatruesIfSupport(m_SupportPhysicalDeviceVulkan12Features.bufferDeviceAddress, m_EnablePhysicalDeviceVulkan12Features.bufferDeviceAddress, "VkPhysicalDeviceVulkan12Features.bufferDeviceAddress");
#endif
#if RAVEN_VK_KHR_ray_tracing_pipeline
			setFeatruesIfSupport(m_SupportPhysicalDeviceVulkan12Features.descriptorIndexing, m_EnablePhysicalDeviceVulkan12Features.descriptorIndexing, "VkPhysicalDeviceVulkan12Features.descriptorIndexing");
			setFeatruesIfSupport(m_SupportPhysicalDeviceRayTracingPipelineFeaturesKHR.rayTracingPipeline, m_EnablePhysicalDeviceRayTracingPipelineFeaturesKHR.rayTracingPipeline, "VkPhysicalDeviceRayTracingPipelineFeaturesKHR.rayTracingPipeline");
			setFeatruesIfSupport(m_SupportPhysicalDeviceRayQueryFeaturesKHR.rayQuery, m_EnablePhysicalDeviceRayQueryFeaturesKHR.rayQuery, "VkPhysicalDeviceRayQueryFeaturesKHR.rayQuery");
#endif
#if RAVEN_VK_EXT_descriptor_buffer
			setFeatruesIfSupport(m_SupportPhysicalDeviceDescriptorBufferFeaturesEXT.descriptorBuffer, m_EnablePhysicalDeviceDescriptorBufferFeaturesEXT.descriptorBuffer, "VkPhysicalDeviceVulkan12Features.bufferDeviceAddress");
#endif
		}

		VkDeviceCreateInfo l_DeviceCreateInfo{};
		l_DeviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		l_DeviceCreateInfo.pNext = R_NULL;
		l_DeviceCreateInfo.queueCreateInfoCount = static_cast<U32>(l_DeviceQueueCreateInfos.size());
		l_DeviceCreateInfo.pQueueCreateInfos = l_DeviceQueueCreateInfos.data();
		l_DeviceCreateInfo.enabledExtensionCount = static_cast<U32>(l_EnableExtensions.size());
		l_DeviceCreateInfo.ppEnabledExtensionNames = l_EnableExtensions.data();
		l_DeviceCreateInfo.pEnabledFeatures = &m_EnablePhysicalDeviceFeatures2.features;

		m_pVkDevice = RAVEN_NEW(RVKDevice)(m_pVkInstance);
		m_pVkDevice->create(l_PhysicalDeviceIdx, l_DeviceCreateInfo, l_QueueFamilyAssignments);
	}
}

Module_vkdrv::~Module_vkdrv() noexcept
{
	RAVEN_DEL(m_pVkDevice);
	m_pVkDevice = R_NULL;
	RAVEN_DEL(m_pVkInstance);
	m_pVkInstance = R_NULL;
}

RAVEN_NAMESPACE_END
