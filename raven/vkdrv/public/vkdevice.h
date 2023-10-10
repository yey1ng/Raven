/*
filename:       vkdevice.h
author:         Raven
date created:   2023-09-07
description:
*/

#pragma once

#include "vkinstance.h"

RAVEN_NAMESPACE_BEGIN

enum class VK_QUEUEFAMILY_USAGE : U16
{
	GRAPHIC_QUEUEFAMILY,
	COMPUTE_QUEUEFAMILY,
	TRANSFER_QUEUEFAMILY,
	PRESENT_QUEUEFAMILY,
	QUEUEFAMILY_COUNT
};

struct VkQueueAssignment
{
	VK_QUEUEFAMILY_USAGE m_QueueFamilyUsage;
	U16             m_QueueFamily;
	U16             m_QueueStart;
	U16             m_QueueCount;
};

class RVKDevice : public RVKInstanceChild
{
public:
	// THE CORE FUNCTIONS
	RAVEN_VULKANFUNCTION_DECL(vkGetDeviceQueue);						// VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkGetDeviceQueue2);                       // VK_VERSION_1_1
	RAVEN_VULKANFUNCTION_DECL(vkCreateCommandPool);                     // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkTrimCommandPool);						// VK_VERSION_1_1
	RAVEN_VULKANFUNCTION_DECL(vkResetCommandPool);						// VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkDestroyCommandPool);					// VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkAllocateCommandBuffers);				// VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkResetCommandBuffer);					// VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkFreeCommandBuffers);					// VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkBeginCommandBuffer);					// VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkEndCommandBuffer);						// VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkQueueSubmit);							// VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkQueueWaitIdle);							// VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCreateFence);							// VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkDestroyFence);							// VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkGetFenceStatus);                        // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkResetFences);                           // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkWaitForFences);                         // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCreateSemaphore);                       // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkDestroySemaphore);                      // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCreateEvent);                           // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkDestroyEvent);                          // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkGetEventStatus);                        // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkSetEvent);                              // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkResetEvent);                            // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkDeviceWaitIdle);                        // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCreateSwapchainKHR);                    // VK_KHR_swapchain
	RAVEN_VULKANFUNCTION_DECL(vkDestroySwapchainKHR);                   // VK_KHR_swapchain
	RAVEN_VULKANFUNCTION_DECL(vkGetSwapchainImagesKHR);                 // VK_KHR_swapchain
	RAVEN_VULKANFUNCTION_DECL(vkAcquireNextImageKHR);                   // VK_KHR_swapchain
	RAVEN_VULKANFUNCTION_DECL(vkAcquireNextImage2KHR);                  // VK_KHR_swapchain
	RAVEN_VULKANFUNCTION_DECL(vkQueuePresentKHR);                       // VK_KHR_swapchain
	RAVEN_VULKANFUNCTION_DECL(vkCreateRenderPass);                      // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkDestroyRenderPass);                     // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCreateBuffer);                          // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkDestroyBuffer);                         // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCreateBufferView);                      // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkDestroyBufferView);                     // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCreateImage);                           // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkDestroyImage);                          // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkGetImageSubresourceLayout);             // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCreateImageView);                       // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkDestroyImageView);                      // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCreateFramebuffer);                     // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkDestroyFramebuffer);                    // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkAllocateDescriptorSets);                // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkFreeDescriptorSets);                    // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkUpdateDescriptorSets);                  // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCreateDescriptorSetLayout);             // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkDestroyDescriptorSetLayout);            // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCreateDescriptorPool);                  // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkDestroyDescriptorPool);                 // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkResetDescriptorPool);                   // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCreateShaderModule);                    // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkDestroyShaderModule);                   // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCreateGraphicsPipelines);               // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkDestroyPipeline);                       // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCreatePipelineLayout);                  // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkDestroyPipelineLayout);                 // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCreatePipelineCache);                   // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkDestroyPipelineCache);                  // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCreateSampler);                         // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkDestroySampler);                        // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCreateQueryPool);                       // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkDestroyQueryPool);                      // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkGetQueryPoolResults);                   // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCreateComputePipelines);                // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkGetPipelineCacheData);                  // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkMergePipelineCaches);                   // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdPipelineBarrier);                    // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdBeginRenderPass);                    // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdNextSubpass);                        // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdEndRenderPass);                      // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdCopyBuffer);                         // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdCopyImage);                          // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdBindPipeline);                       // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdSetViewport);                        // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdSetScissor);                         // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdSetLineWidth);                       // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdSetDepthBias);                       // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdSetBlendConstants);                  // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdSetDepthBounds);                     // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdSetStencilCompareMask);              // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdSetStencilWriteMask);                // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdSetStencilReference);                // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdBindDescriptorSets);                 // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdBindIndexBuffer);                    // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdBindVertexBuffers);                  // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdDraw);                               // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdDrawIndexed);                        // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdDrawIndirect);                       // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdDrawIndexedIndirect);                // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdDispatch);                           // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdDispatchIndirect);                   // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdBlitImage);                          // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdCopyBufferToImage);                  // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdCopyImageToBuffer);                  // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdUpdateBuffer);                       // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdFillBuffer);                         // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdClearColorImage);                    // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdClearDepthStencilImage);             // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdClearAttachments);                   // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdResolveImage);                       // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdSetEvent);                           // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdResetEvent);                         // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdWaitEvents);                         // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdBeginQuery);                         // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdEndQuery);                           // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdResetQueryPool);                     // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdWriteTimestamp);                     // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdCopyQueryPoolResults);               // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdPushConstants);                      // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdExecuteCommands);                    // VK_VERSION_1_0
	RAVEN_VULKANFUNCTION_DECL(vkCmdSetDeviceMask);                      // VK_VERSION_1_1
	RAVEN_VULKANFUNCTION_DECL(vkCmdDispatchBase);                       // VK_VERSION_1_1
	RAVEN_VULKANFUNCTION_DECL(vkCreateRenderPass2);						// VK_VERSION_1_2
	RAVEN_VULKANFUNCTION_DECL(vkCmdBeginRenderPass2);					// VK_VERSION_1_2
	RAVEN_VULKANFUNCTION_DECL(vkCmdNextSubpass2);						// VK_VERSION_1_2	
	RAVEN_VULKANFUNCTION_DECL(vkCmdEndRenderPass2);						// VK_VERSION_1_2
	RAVEN_VULKANFUNCTION_DECL(vkCmdDrawIndirectCount);					// VK_VERSION_1_2
	RAVEN_VULKANFUNCTION_DECL(vkCmdDrawIndexedIndirectCount);			// VK_VERSION_1_2
	RAVEN_VULKANFUNCTION_DECL(vkResetQueryPool);						// VK_VERSION_1_2

#if RAVEN_VK_KHR_synchronization2
	RAVEN_VULKANFUNCTION_DECL(vkCmdSetEvent2KHR);
	RAVEN_VULKANFUNCTION_DECL(vkCmdResetEvent2KHR);
	RAVEN_VULKANFUNCTION_DECL(vkCmdWaitEvents2KHR);
	RAVEN_VULKANFUNCTION_DECL(vkCmdPipelineBarrier2KHR);
	RAVEN_VULKANFUNCTION_DECL(vkCmdWriteTimestamp2KHR);
	RAVEN_VULKANFUNCTION_DECL(vkQueueSubmit2KHR);
#endif

#if RAVEN_VK_KHR_ray_tracing_pipeline
	RAVEN_VULKANFUNCTION_DECL(vkCmdSetRayTracingPipelineStackSizeKHR);           // VK_KHR_ray_tracing_pipeline
	RAVEN_VULKANFUNCTION_DECL(vkCmdTraceRaysIndirectKHR);                        // VK_KHR_ray_tracing_pipeline 
	RAVEN_VULKANFUNCTION_DECL(vkCmdTraceRaysKHR);                                // VK_KHR_ray_tracing_pipeline   
	RAVEN_VULKANFUNCTION_DECL(vkCreateRayTracingPipelinesKHR);                   // VK_KHR_ray_tracing_pipeline
	RAVEN_VULKANFUNCTION_DECL(vkGetRayTracingCaptureReplayShaderGroupHandlesKHR);// VK_KHR_ray_tracing_pipeline
	RAVEN_VULKANFUNCTION_DECL(vkGetRayTracingShaderGroupHandlesKHR);             // VK_KHR_ray_tracing_pipeline
	RAVEN_VULKANFUNCTION_DECL(vkGetRayTracingShaderGroupStackSizeKHR);           // VK_KHR_ray_tracing_pipeline
#endif

#if RAVEN_VK_KHR_push_descriptor
	RAVEN_VULKANFUNCTION_DECL(vkCmdPushDescriptorSetKHR);
#endif 

#if RAVEN_VK_EXT_descriptor_buffer
	RAVEN_VULKANFUNCTION_DECL(vkGetDescriptorSetLayoutSizeEXT);
	RAVEN_VULKANFUNCTION_DECL(vkGetDescriptorSetLayoutBindingOffsetEXT);
	RAVEN_VULKANFUNCTION_DECL(vkGetDescriptorEXT);
	RAVEN_VULKANFUNCTION_DECL(vkCmdBindDescriptorBuffersEXT);
	RAVEN_VULKANFUNCTION_DECL(vkCmdSetDescriptorBufferOffsetsEXT);
#endif 

#if RAVEN_VK_KHR_acceleration_structure
	RAVEN_VULKANFUNCTION_DECL(vkBuildAccelerationStructuresKHR);                // VK_KHR_acceleration_structure
	RAVEN_VULKANFUNCTION_DECL(vkCmdBuildAccelerationStructuresIndirectKHR);     // VK_KHR_acceleration_structure
	RAVEN_VULKANFUNCTION_DECL(vkCmdBuildAccelerationStructuresKHR);             // VK_KHR_acceleration_structure
	RAVEN_VULKANFUNCTION_DECL(vkCmdCopyAccelerationStructureKHR);               // VK_KHR_acceleration_structure
	RAVEN_VULKANFUNCTION_DECL(vkCmdCopyAccelerationStructureToMemoryKHR);       // VK_KHR_acceleration_structure
	RAVEN_VULKANFUNCTION_DECL(vkCmdCopyMemoryToAccelerationStructureKHR);       // VK_KHR_acceleration_structure
	RAVEN_VULKANFUNCTION_DECL(vkCmdWriteAccelerationStructuresPropertiesKHR);   // VK_KHR_acceleration_structure
	RAVEN_VULKANFUNCTION_DECL(vkCopyAccelerationStructureKHR);                  // VK_KHR_acceleration_structure
	RAVEN_VULKANFUNCTION_DECL(vkCopyAccelerationStructureToMemoryKHR);          // VK_KHR_acceleration_structure
	RAVEN_VULKANFUNCTION_DECL(vkCopyMemoryToAccelerationStructureKHR);          // VK_KHR_acceleration_structure
	RAVEN_VULKANFUNCTION_DECL(vkCreateAccelerationStructureKHR);                // VK_KHR_acceleration_structure
	RAVEN_VULKANFUNCTION_DECL(vkDestroyAccelerationStructureKHR);               // VK_KHR_acceleration_structure
	RAVEN_VULKANFUNCTION_DECL(vkGetAccelerationStructureBuildSizesKHR);         // VK_KHR_acceleration_structure
	RAVEN_VULKANFUNCTION_DECL(vkGetAccelerationStructureDeviceAddressKHR);      // VK_KHR_acceleration_structure
	RAVEN_VULKANFUNCTION_DECL(vkGetDeviceAccelerationStructureCompatibilityKHR);// VK_KHR_acceleration_structure
	RAVEN_VULKANFUNCTION_DECL(vkWriteAccelerationStructuresPropertiesKHR);      // VK_KHR_acceleration_structure
#endif

#if RAVEN_VK_KHR_buffer_device_address                                      
	RAVEN_VULKANFUNCTION_DECL(vkGetBufferDeviceAddressKHR);                     // VK_KHR_buffer_device_address                
#endif

	RVKDevice(const RVKDevice&) = delete;
	RVKDevice(RVKDevice&&) = delete;
	RVKDevice& operator=(const RVKDevice&) = delete;
	RVKDevice& operator=(RVKDevice&&) = delete;

	RVKDevice(RVKInstance* i_pVKInstance) noexcept;
	RVKDevice(RVKInstance* i_pVKInstance, U32 i_PhysicalDeviceIdx, VkDeviceCreateInfo& i_CreateInfo, std::vector<VkQueueAssignment>& i_QueueAssignments) noexcept;
	~RVKDevice() noexcept;

	Bool isCreated() const noexcept;
	void create(U32 i_PhysicalDeviceIdx, VkDeviceCreateInfo& i_CreateInfo, std::vector<VkQueueAssignment>& i_QueueAssignments) noexcept;
	void setSurface(VkSurfaceKHR i_Surface) noexcept;
	void destroy() noexcept;
	VkDevice handle() noexcept;

	VkPhysicalDevice getPhysicalDevice() const noexcept;
	U32 getPhysicalDeviceIndex() const noexcept;

	VkDescriptorPool getDescriptorPool() const noexcept;

	U32				getQueueFamilyIndex(VK_QUEUEFAMILY_USAGE i_Usage) const noexcept;
	U32				getQueueCount(VK_QUEUEFAMILY_USAGE i_Usage) const noexcept;
	VkQueue			getQueue(VK_QUEUEFAMILY_USAGE i_Usage, U32 i_Index = 0) const noexcept;
	VkCommandPool	getCommandPool(VK_QUEUEFAMILY_USAGE i_Usage) const noexcept;

	U32				getGraphicsQueueFamilyIndex() const noexcept;
	U32				getGraphicsQueueCount() const noexcept;
	VkQueue			getGraphicsQueue(U32 i_Index = 0) const noexcept;
	VkCommandPool	getGraphicsCommandPool() const noexcept;
	U32				getComputeQueueFamilyIndex() const noexcept;
	U32				getComputeQueueCount() const noexcept;
	VkQueue			getComputeQueue(U32 i_Index = 0) const noexcept;
	VkCommandPool	getComputeCommandPool() const noexcept;
	U32				getTransferQueueFamilyIndex() const noexcept;
	U32				getTransferQueueCount() const noexcept;
	VkQueue			getTransferQueue(U32 i_Index = 0) const noexcept;
	VkCommandPool	getTransferCommandPool() const noexcept;
	U32				getPresentQueueFamilyIndex() const noexcept;
	U32				getPresentQueueCount() const noexcept;
	VkQueue			getPresentQueue(U32 i_Index = 0) const noexcept;
	VkCommandPool	getPresentCommandPool() const noexcept;

	VmaAllocator allocatorVMA() const noexcept;

	void queueSubmit(VkQueue i_Queue, U32 i_SubmitCount, const VkSubmitInfo* i_pSubmit, VkFence i_hFence) noexcept;
	void queueSubmit2KHR(VkQueue i_Queue, U32 i_SubmitCount, const VkSubmitInfo2KHR* i_pSubmit, VkFence i_hFence) noexcept;
	void queuePresent(VkQueue i_Queue, const VkPresentInfoKHR* i_pPresentInfo) noexcept;

private:
	void initVma() noexcept;
	void uninitVma() noexcept;

private:
	U32 m_PhysicalDeviceIdx = 0;
	VkDevice m_hDevice = VK_NULL_HANDLE;
	VkDeviceCreateInfo m_CreateInfo{};
	VkSurfaceKHR m_Surface = VK_NULL_HANDLE;
	VkDescriptorPool m_DescriptorPool = VK_NULL_HANDLE;
	VmaAllocator m_VmaAllocator = VK_NULL_HANDLE;
	VmaVulkanFunctions m_VmaVulkanFunction{};

	struct QueueFamilyInfo_t
	{
		VkQueueFlags			m_QueueFlags;
		std::vector<VkQueue>	m_hQueues;
		VkCommandPool			m_pCommandPool;
	};
	std::vector<QueueFamilyInfo_t>	m_QueueFamilies{};
	std::vector<VkQueueAssignment> m_QueueAssignments{};

	//std::vector<VkQueue> m_GraphicsQueues{};
	//std::optional<VkCommandPool> m_GraphicsCommandPool;
	//std::vector<VkQueue> m_ComputeQueues{};
	//std::optional<VkCommandPool> m_ComputeCommandPool;
	//std::vector<VkQueue> m_TransferQueues{};
	//std::optional<VkCommandPool> m_TransferCommandPool;
	//std::vector<VkQueue> m_PresentQueues{};
	//std::optional<VkCommandPool> m_PresentCommandPool;

	VkPhysicalDeviceFeatures2 m_PhysicalDeviceFeatures2{};
	VkPhysicalDeviceFeatures* m_PhysicalDeviceFeatures = VK_NULL_HANDLE;
	VkPhysicalDeviceVulkan11Features* m_pPhysicalDeviceVulkan11Featrues = VK_NULL_HANDLE;
	VkPhysicalDeviceVulkan12Features* m_pPhysicalDeviceVulkan12Featrues = VK_NULL_HANDLE;
	VkPhysicalDeviceVulkan13Features* m_pPhysicalDeviceVulkan13Featrues = VK_NULL_HANDLE;
	VkPhysicalDeviceSynchronization2FeaturesKHR* m_pPhysicalDeviceSynchronization2FeaturesKHR = VK_NULL_HANDLE;
	VkPhysicalDeviceAccelerationStructureFeaturesKHR* m_pPhysicalDeviceAccelerationStructureFeaturesKHR = VK_NULL_HANDLE;
	VkPhysicalDeviceRayTracingPipelineFeaturesKHR* m_pPhysicalDeviceRayTracingPipelineFeaturesKHR = VK_NULL_HANDLE;
	VkPhysicalDeviceRayQueryFeaturesKHR* m_pPhysicalDeviceRayQueryFeatruesKHR = VK_NULL_HANDLE;
	VkPhysicalDeviceDescriptorBufferFeaturesEXT* m_pPhysicalDeviceDescriptorBufferFeaturesEXT = VK_NULL_HANDLE;
};

RAVEN_NAMESPACE_END