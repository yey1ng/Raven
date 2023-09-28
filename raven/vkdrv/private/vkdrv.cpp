/*
filename:       vkdrv.cpp
author:         Raven
date created:   2023-09-27
description:
*/

#include <vkdrv/public/module_vkdrv.h>

RAVEN_NAMESPACE_BEGIN

RAVEN_MODULE_IMPLEMENTATION(vkdrv)

Module_vkdrv::Module_vkdrv() noexcept
{
	VkInstanceCreateInfo l_test;
	m_VkInstance = RAVEN_New(RVKInstance)(l_test);
}

RAVEN_NAMESPACE_END
