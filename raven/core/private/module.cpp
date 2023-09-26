/*
filename:       module.h
author:         Raven
date created:   2023-09-06
description:
*/

#include <core/public/module.h>

RAVEN_NAMESPACE_BEGIN

RAVEN_MODULE_IMPLEMENTATION(base)

Module_base::Module_base() noexcept {
	m_pModule = this;
}

Module_base::~Module_base() noexcept {
	m_pModule = R_NULL;
}

RAVEN_NAMESPACE_END
