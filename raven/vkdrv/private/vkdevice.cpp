/*
filename:       vkdevice.cpp
author:         Raven
date created:   2023-09-07
description:
*/

#include <vkdrv/public/vkdevice.h>

RAVEN_NAMESPACE_BEGIN

RVKDevice::RVKDevice(RVKInstance* i_pVKInstance) noexcept
	: RVKInstanceChild(i_pVKInstance)
{

}

RVKDevice::RVKDevice(RVKInstance* i_pVKInstance, U32 i_PhysicalDeviceIdx, VkDeviceCreateInfo& i_CreateInfo, std::vector<VkQueueAssignment>& i_QueueAssignments) noexcept
	: RVKInstanceChild(i_pVKInstance)
{
	create(i_PhysicalDeviceIdx, i_CreateInfo, i_QueueAssignments);
}

RVKDevice::~RVKDevice()
{
	if (isCreated())
		destroy();
}

Bool RVKDevice::isCreated() const noexcept
{
	return m_hDevice != VK_NULL_HANDLE;
}

void RVKDevice::create(U32 i_PhysicalDeviceIdx, VkDeviceCreateInfo& i_CreateInfo, std::vector<VkQueueAssignment>& i_QueueAssignments) noexcept
{
	if (isCreated())
		R_LOG_ERROR("VKDevice is Created");

	VkResult l_Result = instance().rvkCreateDevice(instance().getPhysicalDevice(i_PhysicalDeviceIdx), &i_CreateInfo, allocatorVK(), &m_hDevice);
	if (l_Result != VK_SUCCESS)
		R_LOG_ERROR("VKDevice Create failed");

	m_PhysicalDeviceIdx = std::move(i_PhysicalDeviceIdx);
	m_CreateInfo = std::move(i_CreateInfo);
	m_QueueAssignments = std::move(i_QueueAssignments);

	RAVEN_VULKANFUNCTION_DEVICE(vkGetDeviceQueue, m_hDevice);						// VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkGetDeviceQueue2, m_hDevice);                      // VK_VERSION_1_1
	RAVEN_VULKANFUNCTION_DEVICE(vkCreateCommandPool, m_hDevice);                    // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkTrimCommandPool, m_hDevice);                      // VK_VERSION_1_1
	RAVEN_VULKANFUNCTION_DEVICE(vkResetCommandPool, m_hDevice);                     // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkDestroyCommandPool, m_hDevice);                   // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkAllocateCommandBuffers, m_hDevice);               // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkResetCommandBuffer, m_hDevice);                   // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkFreeCommandBuffers, m_hDevice);                   // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkBeginCommandBuffer, m_hDevice);                   // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkEndCommandBuffer, m_hDevice);                     // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkQueueSubmit, m_hDevice);                          // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkQueueWaitIdle, m_hDevice);                        // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCreateFence, m_hDevice);                          // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkDestroyFence, m_hDevice);                         // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkGetFenceStatus, m_hDevice);                       // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkResetFences, m_hDevice);                          // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkWaitForFences, m_hDevice);                        // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCreateSemaphore, m_hDevice);                      // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkDestroySemaphore, m_hDevice);                     // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCreateEvent, m_hDevice);                          // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkDestroyEvent, m_hDevice);                         // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkGetEventStatus, m_hDevice);                       // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkSetEvent, m_hDevice);                             // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkResetEvent, m_hDevice);                           // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkDeviceWaitIdle, m_hDevice);                       // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCreateSwapchainKHR, m_hDevice);                   // VK_KHR_swapchain
	RAVEN_VULKANFUNCTION_DEVICE(vkDestroySwapchainKHR, m_hDevice);                  // VK_KHR_swapchain
	RAVEN_VULKANFUNCTION_DEVICE(vkGetSwapchainImagesKHR, m_hDevice);                // VK_KHR_swapchain
	RAVEN_VULKANFUNCTION_DEVICE(vkAcquireNextImageKHR, m_hDevice);                  // VK_KHR_swapchain
	RAVEN_VULKANFUNCTION_DEVICE(vkAcquireNextImage2KHR, m_hDevice);                 // VK_KHR_swapchain
	RAVEN_VULKANFUNCTION_DEVICE(vkQueuePresentKHR, m_hDevice);                      // VK_KHR_swapchain
	RAVEN_VULKANFUNCTION_DEVICE(vkCreateRenderPass, m_hDevice);                     // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkDestroyRenderPass, m_hDevice);                    // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCreateBuffer, m_hDevice);                         // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkDestroyBuffer, m_hDevice);                        // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCreateBufferView, m_hDevice);                     // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkDestroyBufferView, m_hDevice);                    // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCreateImage, m_hDevice);                          // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkDestroyImage, m_hDevice);                         // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkGetImageSubresourceLayout, m_hDevice);            // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCreateImageView, m_hDevice);                      // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkDestroyImageView, m_hDevice);                     // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCreateFramebuffer, m_hDevice);                    // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkDestroyFramebuffer, m_hDevice);                   // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkAllocateDescriptorSets, m_hDevice);               // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkFreeDescriptorSets, m_hDevice);                   // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkUpdateDescriptorSets, m_hDevice);                 // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCreateDescriptorSetLayout, m_hDevice);            // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkDestroyDescriptorSetLayout, m_hDevice);           // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCreateDescriptorPool, m_hDevice);                 // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkDestroyDescriptorPool, m_hDevice);                // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkResetDescriptorPool, m_hDevice);                  // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCreateShaderModule, m_hDevice);                   // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkDestroyShaderModule, m_hDevice);                  // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCreateGraphicsPipelines, m_hDevice);              // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkDestroyPipeline, m_hDevice);                      // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCreatePipelineLayout, m_hDevice);                 // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkDestroyPipelineLayout, m_hDevice);                // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCreatePipelineCache, m_hDevice);                  // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkDestroyPipelineCache, m_hDevice);                 // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCreateSampler, m_hDevice);                        // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkDestroySampler, m_hDevice);                       // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCreateQueryPool, m_hDevice);                      // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkDestroyQueryPool, m_hDevice);                     // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkGetQueryPoolResults, m_hDevice);                  // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCreateComputePipelines, m_hDevice);               // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkGetPipelineCacheData, m_hDevice);                 // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkMergePipelineCaches, m_hDevice);                  // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdPipelineBarrier, m_hDevice);                   // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdBeginRenderPass, m_hDevice);                   // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdNextSubpass, m_hDevice);                       // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdEndRenderPass, m_hDevice);                     // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdCopyBuffer, m_hDevice);                        // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdCopyImage, m_hDevice);                         // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdBindPipeline, m_hDevice);                      // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdSetViewport, m_hDevice);                       // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdSetScissor, m_hDevice);                        // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdSetLineWidth, m_hDevice);                      // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdSetDepthBias, m_hDevice);                      // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdSetBlendConstants, m_hDevice);                 // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdSetDepthBounds, m_hDevice);                    // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdSetStencilCompareMask, m_hDevice);             // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdSetStencilWriteMask, m_hDevice);               // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdSetStencilReference, m_hDevice);               // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdBindDescriptorSets, m_hDevice);                // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdBindIndexBuffer, m_hDevice);                   // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdBindVertexBuffers, m_hDevice);                 // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdDraw, m_hDevice);                              // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdDrawIndexed, m_hDevice);                       // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdDrawIndirect, m_hDevice);                      // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdDrawIndexedIndirect, m_hDevice);               // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdDispatch, m_hDevice);                          // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdDispatchIndirect, m_hDevice);                  // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdBlitImage, m_hDevice);                         // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdCopyBufferToImage, m_hDevice);                 // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdCopyImageToBuffer, m_hDevice);                 // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdUpdateBuffer, m_hDevice);                      // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdFillBuffer, m_hDevice);                        // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdClearColorImage, m_hDevice);                   // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdClearDepthStencilImage, m_hDevice);            // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdClearAttachments, m_hDevice);                  // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdResolveImage, m_hDevice);                      // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdSetEvent, m_hDevice);                          // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdResetEvent, m_hDevice);                        // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdWaitEvents, m_hDevice);                        // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdBeginQuery, m_hDevice);                        // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdEndQuery, m_hDevice);                          // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdResetQueryPool, m_hDevice);                    // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdWriteTimestamp, m_hDevice);                    // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdCopyQueryPoolResults, m_hDevice);              // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdPushConstants, m_hDevice);                     // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdExecuteCommands, m_hDevice);                   // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdSetDeviceMask, m_hDevice);                     // VK_VERSION_1_1
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdDispatchBase, m_hDevice);                      // VK_VERSION_1_1

	RAVEN_VULKANFUNCTION_DEVICE(vkCreateRenderPass2, m_hDevice);
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdBeginRenderPass2, m_hDevice);
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdNextSubpass2, m_hDevice);
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdEndRenderPass2, m_hDevice);
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdDrawIndirectCount, m_hDevice);
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdDrawIndexedIndirectCount, m_hDevice);
	RAVEN_VULKANFUNCTION_DEVICE(vkResetQueryPool, m_hDevice);

#if RAVEN_VK_KHR_synchronization2
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdSetEvent2KHR, m_hDevice);
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdResetEvent2KHR, m_hDevice);
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdWaitEvents2KHR, m_hDevice);
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdPipelineBarrier2KHR, m_hDevice);
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdWriteTimestamp2KHR, m_hDevice);
	RAVEN_VULKANFUNCTION_DEVICE(vkQueueSubmit2KHR, m_hDevice);
#endif

#if RAVEN_VK_KHR_ray_tracing_pipeline
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdSetRayTracingPipelineStackSizeKHR, m_hDevice);            // VK_KHR_ray_tracing_pipeline
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdTraceRaysIndirectKHR, m_hDevice);                         // VK_KHR_ray_tracing_pipeline 
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdTraceRaysKHR, m_hDevice);                                 // VK_KHR_ray_tracing_pipeline   
	RAVEN_VULKANFUNCTION_DEVICE(vkCreateRayTracingPipelinesKHR, m_hDevice);                    // VK_KHR_ray_tracing_pipeline
	RAVEN_VULKANFUNCTION_DEVICE(vkGetRayTracingCaptureReplayShaderGroupHandlesKHR, m_hDevice); // VK_KHR_ray_tracing_pipeline
	RAVEN_VULKANFUNCTION_DEVICE(vkGetRayTracingShaderGroupHandlesKHR, m_hDevice);              // VK_KHR_ray_tracing_pipeline
	RAVEN_VULKANFUNCTION_DEVICE(vkGetRayTracingShaderGroupStackSizeKHR, m_hDevice);            // VK_KHR_ray_tracing_pipeline
#endif

#if RAVEN_VK_KHR_push_descriptor
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdPushDescriptorSetKHR, m_hDevice);
#endif 

#if RAVEN_VK_EXT_descriptor_buffer
	RAVEN_VULKANFUNCTION_DEVICE(vkGetDescriptorSetLayoutSizeEXT, m_hDevice);
	RAVEN_VULKANFUNCTION_DEVICE(vkGetDescriptorSetLayoutBindingOffsetEXT, m_hDevice);
	RAVEN_VULKANFUNCTION_DEVICE(vkGetDescriptorEXT, m_hDevice);
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdBindDescriptorBuffersEXT, m_hDevice);
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdSetDescriptorBufferOffsetsEXT, m_hDevice);
#endif

#if RAVEN_VK_KHR_acceleration_structure
	RAVEN_VULKANFUNCTION_DEVICE(vkBuildAccelerationStructuresKHR, m_hDevice);                  // VK_KHR_acceleration_structure
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdBuildAccelerationStructuresIndirectKHR, m_hDevice);       // VK_KHR_acceleration_structure
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdBuildAccelerationStructuresKHR, m_hDevice);               // VK_KHR_acceleration_structure
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdCopyAccelerationStructureKHR, m_hDevice);                 // VK_KHR_acceleration_structure
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdCopyAccelerationStructureToMemoryKHR, m_hDevice);         // VK_KHR_acceleration_structure
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdCopyMemoryToAccelerationStructureKHR, m_hDevice);         // VK_KHR_acceleration_structure
	RAVEN_VULKANFUNCTION_DEVICE(vkCmdWriteAccelerationStructuresPropertiesKHR, m_hDevice);     // VK_KHR_acceleration_structure
	RAVEN_VULKANFUNCTION_DEVICE(vkCopyAccelerationStructureKHR, m_hDevice);                    // VK_KHR_acceleration_structure
	RAVEN_VULKANFUNCTION_DEVICE(vkCopyAccelerationStructureToMemoryKHR, m_hDevice);            // VK_KHR_acceleration_structure
	RAVEN_VULKANFUNCTION_DEVICE(vkCopyMemoryToAccelerationStructureKHR, m_hDevice);            // VK_KHR_acceleration_structure
	RAVEN_VULKANFUNCTION_DEVICE(vkCreateAccelerationStructureKHR, m_hDevice);                  // VK_KHR_acceleration_structure
	RAVEN_VULKANFUNCTION_DEVICE(vkDestroyAccelerationStructureKHR, m_hDevice);                 // VK_KHR_acceleration_structure
	RAVEN_VULKANFUNCTION_DEVICE(vkGetAccelerationStructureBuildSizesKHR, m_hDevice);           // VK_KHR_acceleration_structure
	RAVEN_VULKANFUNCTION_DEVICE(vkGetAccelerationStructureDeviceAddressKHR, m_hDevice);        // VK_KHR_acceleration_structure
	RAVEN_VULKANFUNCTION_DEVICE(vkGetDeviceAccelerationStructureCompatibilityKHR, m_hDevice);  // VK_KHR_acceleration_structure
	RAVEN_VULKANFUNCTION_DEVICE(vkWriteAccelerationStructuresPropertiesKHR, m_hDevice);        // VK_KHR_acceleration_structure
#endif

#if RAVEN_VK_KHR_buffer_device_address                                      
	RAVEN_VULKANFUNCTION_DEVICE(vkGetBufferDeviceAddressKHR, m_hDevice);                       // VK_KHR_buffer_device_address                
#endif
	// Create DescriptorPool
	{
		VkDescriptorPoolCreateInfo l_DescriptorPoolCreateInfo{};
		l_DescriptorPoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		l_DescriptorPoolCreateInfo.pNext = R_NULL;
		l_DescriptorPoolCreateInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT | VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT;
		l_DescriptorPoolCreateInfo.maxSets = RAVEN_VK_MAX_DESCRIPTORSET;
		l_DescriptorPoolCreateInfo.poolSizeCount = RAVEN_VK_MAX_DESCRIPTOR_TYPE;

		std::vector<VkDescriptorPoolSize> l_DescriptorPoolSizes(RAVEN_VK_MAX_DESCRIPTOR_TYPE);
		l_DescriptorPoolSizes[0] = { VK_DESCRIPTOR_TYPE_SAMPLER, RAVEN_VK_MAX_DESCRIPTOR_SAMPLER };
		l_DescriptorPoolSizes[1] = { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, RAVEN_VK_MAX_DESCRIPTOR_COMBINED_IMAGE_SAMPLER };
		l_DescriptorPoolSizes[2] = { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, RAVEN_VK_MAX_DESCRIPTOR_SAMPLED_IMAGE };
		l_DescriptorPoolSizes[3] = { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, RAVEN_VK_MAX_DESCRIPTOR_STORAGE_IMAGE };
		l_DescriptorPoolSizes[4] = { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, RAVEN_VK_MAX_DESCRIPTOR_UNIFORM_TEXEL_BUFFER };
		l_DescriptorPoolSizes[5] = { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, RAVEN_VK_MAX_DESCRIPTOR_STORAGE_TEXEL_BUFFER };
		l_DescriptorPoolSizes[6] = { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, RAVEN_VK_MAX_DESCRIPTOR_UNIFORM_BUFFER };
		l_DescriptorPoolSizes[7] = { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, RAVEN_VK_MAX_DESCRIPTOR_STORAGE_BUFFER };
		l_DescriptorPoolSizes[8] = { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, RAVEN_VK_MAX_DESCRIPTOR_UNIFORM_BUFFER_DYNAMIC };
		l_DescriptorPoolSizes[9] = { VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR, RAVEN_VK_MAX_DESCRIPTOR_ACCELERATION_STRUCTURES };

		rvkCreateDescriptorPool(m_hDevice, &l_DescriptorPoolCreateInfo, allocatorVK(), &m_DescriptorPool);
	}

	//Create QueueFamily
	{
		VkCommandPoolCreateInfo l_CommandPoolCreateInfo{};
		l_CommandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		l_CommandPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		l_CommandPoolCreateInfo.pNext = R_NULL;
		const VkDeviceQueueCreateInfo* l_DeviceQueueCreateInfos = m_CreateInfo.pQueueCreateInfos;

		// update queue family and queue assignment information
		std::vector<VkQueueFamilyProperties2> l_QueueFamilies = instance().getPhysicalDeviceQueueFamilyProperties(m_PhysicalDeviceIdx);
		m_QueueFamilies.reserve(l_QueueFamilies.size());
		for(const auto& l_QueueFamily : l_QueueFamilies)
		{
			QueueFamilyInfo_t l_QueueFamilyInfo{};
			l_QueueFamilyInfo.m_QueueFlags = l_QueueFamily.queueFamilyProperties.queueFlags;
			l_QueueFamilyInfo.m_pCommandPool = R_NULL;

			m_QueueFamilies.emplace_back(std::move(l_QueueFamilyInfo));
		}

		for (U32 i = 0; i < m_CreateInfo.queueCreateInfoCount; ++i)
		{
			const auto& l_QueueCreateInfo = m_CreateInfo.pQueueCreateInfos[i];
			for (U32 j = 0; j < l_QueueCreateInfo.queueCount; ++j)
			{
				VkQueue l_Queue{};
				VkDeviceQueueInfo2 l_QueueInfo2{};
				l_QueueInfo2.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2;
				l_QueueInfo2.queueFamilyIndex = l_QueueCreateInfo.queueFamilyIndex;
				l_QueueInfo2.queueIndex = j;
				m_QueueFamilies[l_QueueCreateInfo.queueFamilyIndex].m_hQueues.push_back(l_Queue);
			}
			rvkCreateCommandPool(m_hDevice, &l_CommandPoolCreateInfo, allocatorVK(), &m_QueueFamilies[l_QueueCreateInfo.queueFamilyIndex].m_pCommandPool);
		}
	}

	initVma();
	R_LOG_INFO("VKDevice create success");
}

void RVKDevice::setSurface(VkSurfaceKHR i_Surface) noexcept
{
	m_Surface = i_Surface;
}

void RVKDevice::destroy() noexcept
{
	if (!isCreated())
		R_LOG_ERROR("VkDevice isn't destroy");

	uninitVma();

	for (U32 i = 0; i < m_CreateInfo.queueCreateInfoCount; ++i)
	{
		U32 l_QueueFamilyIndex = m_CreateInfo.pQueueCreateInfos[i].queueFamilyIndex;
		rvkDestroyCommandPool(m_hDevice, m_QueueFamilies[l_QueueFamilyIndex].m_pCommandPool, allocatorVK());
	}

	rvkDestroyDescriptorPool(m_hDevice, m_DescriptorPool, allocatorVK());
	m_DescriptorPool = VK_NULL_HANDLE;

	instance().rvkDestroyDevice(m_hDevice, allocatorVK());
	m_hDevice = VK_NULL_HANDLE;

	R_LOG_INFO("VKDevice Destroy");
}

VkDevice RVKDevice::handle() noexcept
{
	return m_hDevice;
}

VkPhysicalDevice RVKDevice::getPhysicalDevice() const noexcept
{
	return instance().getPhysicalDevice(m_PhysicalDeviceIdx);
}

U32 RVKDevice::getPhysicalDeviceIndex() const noexcept
{
	return m_PhysicalDeviceIdx;
}

VkDescriptorPool RVKDevice::getDescriptorPool() const noexcept
{
	return m_DescriptorPool;
}

U32	RVKDevice::getQueueFamilyIndex(VK_QUEUEFAMILY_USAGE i_Usage) const noexcept
{
	return m_QueueAssignments[static_cast<U16>(i_Usage)].m_QueueFamily;
}

U32	RVKDevice::getQueueCount(VK_QUEUEFAMILY_USAGE i_Usage) const noexcept
{
	return m_QueueAssignments[static_cast<U16>(i_Usage)].m_QueueCount;
}

VkQueue	RVKDevice::getQueue(VK_QUEUEFAMILY_USAGE i_Usage, U32 i_Index) const noexcept
{
	R_LOG_FATAL(i_Index < getQueueCount(i_Usage), "Index > QueueCout!");
	R_LOG_FATAL((m_QueueAssignments[static_cast<U16>(i_Usage)].m_QueueStart + i_Index) < m_QueueFamilies[getQueueFamilyIndex(i_Usage)].m_hQueues.size(), "Not Found Queue Index");

	return m_QueueFamilies[getQueueFamilyIndex(i_Usage)].m_hQueues[m_QueueAssignments[static_cast<U16>(i_Usage)].m_QueueStart + i_Index];
}

VkCommandPool RVKDevice::getCommandPool(VK_QUEUEFAMILY_USAGE i_Usage) const noexcept
{
	return m_QueueFamilies[getQueueFamilyIndex(i_Usage)].m_pCommandPool;
}

U32	RVKDevice::getGraphicsQueueFamilyIndex() const noexcept
{
	return getQueueFamilyIndex(VK_QUEUEFAMILY_USAGE::GRAPHIC_QUEUEFAMILY);
}

U32	RVKDevice::getGraphicsQueueCount() const noexcept
{
	return getQueueCount(VK_QUEUEFAMILY_USAGE::GRAPHIC_QUEUEFAMILY);
}

VkQueue	RVKDevice::getGraphicsQueue(U32 i_Index) const noexcept
{
	return getQueue(VK_QUEUEFAMILY_USAGE::GRAPHIC_QUEUEFAMILY);
}

VkCommandPool RVKDevice::getGraphicsCommandPool() const noexcept
{
	return getCommandPool(VK_QUEUEFAMILY_USAGE::GRAPHIC_QUEUEFAMILY);
}

U32	RVKDevice::getComputeQueueFamilyIndex() const noexcept
{
	return getQueueFamilyIndex(VK_QUEUEFAMILY_USAGE::COMPUTE_QUEUEFAMILY);
}

U32	RVKDevice::getComputeQueueCount() const noexcept
{
	return getQueueCount(VK_QUEUEFAMILY_USAGE::COMPUTE_QUEUEFAMILY);
}

VkQueue	RVKDevice::getComputeQueue(U32 i_Index) const noexcept
{
	return getQueue(VK_QUEUEFAMILY_USAGE::COMPUTE_QUEUEFAMILY);
}
VkCommandPool RVKDevice::getComputeCommandPool() const noexcept
{
	return getCommandPool(VK_QUEUEFAMILY_USAGE::COMPUTE_QUEUEFAMILY);
}

U32	RVKDevice::getTransferQueueFamilyIndex() const noexcept
{
	return getQueueFamilyIndex(VK_QUEUEFAMILY_USAGE::TRANSFER_QUEUEFAMILY);
}

U32	RVKDevice::getTransferQueueCount() const noexcept
{
	return getQueueCount(VK_QUEUEFAMILY_USAGE::TRANSFER_QUEUEFAMILY);
}

VkQueue	RVKDevice::getTransferQueue(U32 i_Index) const noexcept
{
	return getQueue(VK_QUEUEFAMILY_USAGE::TRANSFER_QUEUEFAMILY);
}

VkCommandPool RVKDevice::getTransferCommandPool() const noexcept
{
	return getCommandPool(VK_QUEUEFAMILY_USAGE::TRANSFER_QUEUEFAMILY);
}

U32	RVKDevice::getPresentQueueFamilyIndex() const noexcept
{
	return getQueueFamilyIndex(VK_QUEUEFAMILY_USAGE::PRESENT_QUEUEFAMILY);
}

U32	RVKDevice::getPresentQueueCount() const noexcept
{
	return getQueueCount(VK_QUEUEFAMILY_USAGE::PRESENT_QUEUEFAMILY);
}

VkQueue	RVKDevice::getPresentQueue(U32 i_Index) const noexcept
{
	return getQueue(VK_QUEUEFAMILY_USAGE::PRESENT_QUEUEFAMILY);
}

VkCommandPool RVKDevice::getPresentCommandPool() const noexcept
{
	return getCommandPool(VK_QUEUEFAMILY_USAGE::PRESENT_QUEUEFAMILY);
}

VmaAllocator RVKDevice::allocatorVMA() const noexcept
{
	return m_VmaAllocator;
}

void RVKDevice::queueSubmit(VkQueue i_Queue, U32 i_SubmitCount, const VkSubmitInfo* i_pSubmit, VkFence i_hFence) noexcept
{
	VkResult l_Result = vkQueueSubmit(i_Queue, i_SubmitCount, i_pSubmit, i_hFence);
	if (l_Result == VK_SUCCESS)
		return;
	else if (l_Result == VK_ERROR_OUT_OF_HOST_MEMORY)
		R_LOG_ERROR("queueSubmit out of host memory");
	else if (l_Result == VK_ERROR_OUT_OF_DEVICE_MEMORY)
		R_LOG_ERROR("queueSubmit out of device memory");
	else if (l_Result == VK_ERROR_DEVICE_LOST)
		R_LOG_ERROR("queueSubmit device lost");
	else
		R_LOG_ERROR("queueSubmit failed");
}

void RVKDevice::queueSubmit2KHR(VkQueue i_Queue, U32 i_SubmitCount, const VkSubmitInfo2KHR* i_pSubmit, VkFence i_hFence) noexcept
{
	VkResult l_Result = vkQueueSubmit2(i_Queue, i_SubmitCount, i_pSubmit, i_hFence);
	if (l_Result == VK_SUCCESS)
		return;
	else if (l_Result == VK_ERROR_OUT_OF_HOST_MEMORY)
		R_LOG_ERROR("queueSubmit2 out of host memory");
	else if (l_Result == VK_ERROR_OUT_OF_DEVICE_MEMORY)
		R_LOG_ERROR("queueSubmit2 out of device memory");
	else if (l_Result == VK_ERROR_DEVICE_LOST)
		R_LOG_ERROR("queueSubmit2 device lost");
	else
		R_LOG_ERROR("queueSubmit2 failed");
}

void RVKDevice::queuePresent(VkQueue i_Queue, const VkPresentInfoKHR* i_pPresentInfo) noexcept
{
	VkResult l_Result = vkQueuePresentKHR(i_Queue, i_pPresentInfo);
	if (l_Result == VK_SUCCESS)
		return;
	else if (l_Result == VK_SUBOPTIMAL_KHR)
		R_LOG_ERROR("queuePresent suboptimal");
	else
		R_LOG_ERROR("queuePresent failed");
}

void RVKDevice::initVma() noexcept
{
	VmaAllocatorCreateInfo l_CreateInfo = {};
	l_CreateInfo.vulkanApiVersion = VK_API_VERSION_1_3;
	l_CreateInfo.physicalDevice = instance().getPhysicalDevice(m_PhysicalDeviceIdx);
	l_CreateInfo.device = m_hDevice;
	l_CreateInfo.instance = instance().handle();
	memset((Char*)&m_VmaVulkanFunction, sizeof(m_VmaVulkanFunction), 0);
	m_VmaVulkanFunction.vkGetInstanceProcAddr = &vkGetInstanceProcAddr;
	m_VmaVulkanFunction.vkGetDeviceProcAddr = &vkGetDeviceProcAddr;
	l_CreateInfo.pVulkanFunctions = &m_VmaVulkanFunction;
#if RAVEN_VK_KHR_buffer_device_address
	l_CreateInfo.flags |= VMA_ALLOCATOR_CREATE_BUFFER_DEVICE_ADDRESS_BIT;
#endif

	VkResult l_Result = vmaCreateAllocator(&l_CreateInfo, &m_VmaAllocator);
	if (l_Result != VK_SUCCESS)
		R_LOG_INFO("VKDevice init success");
	else
		R_LOG_ERROR("VKDevice init error");
}

void RVKDevice::uninitVma() noexcept
{
	vmaDestroyAllocator(m_VmaAllocator);
	m_VmaAllocator = VK_NULL_HANDLE;
}

RAVEN_NAMESPACE_END