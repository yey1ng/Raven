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
	Module_vkdrv() noexcept;
	virtual ~Module_vkdrv() noexcept;

private:
	RVKInstance* m_VkInstance = R_NULL;
	RVKDevice* m_VkDevice = R_NULL;
};

RAVEN_NAMESPACE_END