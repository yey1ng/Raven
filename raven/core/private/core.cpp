/*
filename:       core.cpp
author:         Raven
date created:   2023-09-25
description:
*/

#include <core/public/module_core.h>
#include <clocale>

RAVEN_NAMESPACE_BEGIN

RAVEN_CORE_API void* RAVEN_NullPtr() noexcept
{
	return R_NULL;
}

RAVEN_MODULE_IMPLEMENTATION(core);

Module_core::Module_core() noexcept
{
	RAVEN_MODULE_CONSTRUCTOR_CODE(core);

	R_LOG_INFO("Module Core Init");
}

Module_core::~Module_core() noexcept
{
	R_LOG_INFO("Module Core UnInit");

	RAVEN_MODULE_DESTRUCTOR_CODE(core);
}

RAVEN_NAMESPACE_END