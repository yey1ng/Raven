/*
filename:       vkcore.cpp
author:         Raven
date created:   2023-09-06
description:
*/

#pragma once
#include "vkdefine.h"
#include <core/public/module.h>
#include <configuration_vkdrv.h>

#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>
#define VMA_STATIC_VULKAN_FUNCTIONS 0
#define VMA_DYNAMIC_VULKAN_FUNCTIONS 1
#include <vk_mem_alloc.h>

#define RAVEN_VKBOOL(v)								((v) ? VK_TRUE : VK_FALSE)

#define RAVEN_VULKANFUNCTION_DECL(func)				PFN_##func r##func = VK_NULL_HANDLE;
#define RAVEN_VULKANFUNCTION_INSTANCE(func, inst)	r##func = (PFN_##func)vkGetInstanceProcAddr(inst, #func);
#define RAVEN_VULKANFUNCTION_DEVICE(func, dev)		r##func = (PFN_##func)vkGetDeviceProcAddr(dev, #func);

RAVEN_NAMESPACE_BEGIN

class RAVEN_VKDRV_API Module_vkcore : virtual public Module_base
{
	RAVEN_MODULE_DECLARATION(vkcore);

public:
	RAVEN_VULKANFUNCTION_DECL(vkEnumerateInstanceVersion);
	RAVEN_VULKANFUNCTION_DECL(vkEnumerateInstanceLayerProperties);
	RAVEN_VULKANFUNCTION_DECL(vkEnumerateInstanceExtensionProperties);
	RAVEN_VULKANFUNCTION_DECL(vkCreateInstance);

public:
	Module_vkcore() noexcept;
	virtual ~Module_vkcore() noexcept;

	VkAllocationCallbacks* getVkAllocator() noexcept;
};

RAVEN_NAMESPACE_END