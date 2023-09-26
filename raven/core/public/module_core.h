/*
filename:       module_core.h
author:         Raven
date created:   2023-09-25
description:
*/

#pragma once

#include "module.h"
#include "configuration_core.h"

RAVEN_NAMESPACE_BEGIN

class RAVEN_CORE_API Module_core : virtual public Module_base
{
	RAVEN_MODULE_DECLARATION(core);

public:
	Module_core() noexcept;
	virtual ~Module_core() noexcept;
};

RAVEN_NAMESPACE_END