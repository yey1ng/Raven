/*
filename:       vkcore.cpp
author:         Raven
date created:   2023-09-06
description:
*/

#include <vkdrv/public/vkcore.h>

RAVEN_NAMESPACE_BEGIN

RAVEN_MODULE_IMPLEMENTATION(vkcore)

Module_vkcore::Module_vkcore() noexcept
{
	RAVEN_MODULE_CONSTRUCTOR_CODE(vkcore);

	RAVEN_VULKANFUNCTION_INSTANCE(vkEnumerateInstanceVersion, R_NULL);
	RAVEN_VULKANFUNCTION_INSTANCE(vkEnumerateInstanceLayerProperties, R_NULL);
	RAVEN_VULKANFUNCTION_INSTANCE(vkEnumerateInstanceExtensionProperties, R_NULL);
	RAVEN_VULKANFUNCTION_INSTANCE(vkCreateInstance, R_NULL);
}

Module_vkcore::~Module_vkcore() noexcept
{
	RAVEN_MODULE_DESTRUCTOR_CODE(vkcore);
}

VkAllocationCallbacks* Module_vkcore::getVkAllocator() noexcept
{
	return R_NULL;
}

RAVEN_NAMESPACE_END