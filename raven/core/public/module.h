/*
filename:       module.h
author:         Raven
date created:   2023-09-06
description:
*/

#pragma once

#include "defines.h"
#include "typedefs.h"
#include "logger.h"

RAVEN_NAMESPACE_BEGIN

#define RAVEN_MODULE_DECLARATION(MOD_NAME)					\
private:													\
	static Module_##MOD_NAME* m_pModule;					\
public:														\
	static Module_##MOD_NAME& module() noexcept;			\
	static Module_##MOD_NAME* modulePtr() noexcept;			\
private:

#define RAVEN_MODULE_IMPLEMENTATION(MOD_NAME)				\
Module_##MOD_NAME* Module_##MOD_NAME::m_pModule = R_NULL;	\
Module_##MOD_NAME& Module_##MOD_NAME::module() noexcept		\
{															\
	return *m_pModule;										\
}															\
Module_##MOD_NAME* Module_##MOD_NAME::modulePtr() noexcept	\
{															\
	return m_pModule;										\
}															\

#define RAVEN_MODULE_CONSTRUCTOR_CODE(MOD_NAME)				\
m_pModule = this;

#define RAVEN_MODULE_DESTRUCTOR_CODE(MOD_NAME)				\
m_pModule = R_NULL;

#define RAVEN_MODULE(MOD_NAME)						RAVEN_NS::Module_##MOD_NAME::module()
#define RAVEN_MODULEPTR(MOD_NAME)					RAVEN_NS::Module_##MOD_NAME::modulePtr()
#define RAVEN_MODULE_INIT(MOD_NAME)					new RAVEN_NS::DModule_##MOD_NAME;
#define RAVEN_MODULE_UNINIT(MOD_NAME)				delete RAVEN_MODULEPTR(MOD_NAME)

class RAVEN_CORE_API Module_base
{
	RAVEN_MODULE_DECLARATION(base);

public:
	Module_base() noexcept;
	virtual ~Module_base() noexcept;
};

std::string formatString(const char* format, ...) {
	const int bufferSize = 1024; 
	char buffer[bufferSize];

	va_list args;
	va_start(args, format);
	std::vsnprintf(buffer, bufferSize, format, args);
	va_end(args);

	return std::string(buffer);
}

RAVEN_NAMESPACE_END