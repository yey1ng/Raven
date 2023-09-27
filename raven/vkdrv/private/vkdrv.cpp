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
	m_VkInstance = new 
}

RAVEN_NAMESPACE_END

#define DOME_PP_OVERLOAD(FUNC, ...)                                                         \
BOOST_PP_IF(                                                                                \
    BOOST_PP_IS_EMPTY(__VA_ARGS__),                                                         \
    FUNC##0(),                                                                              \
    BOOST_PP_CAT(BOOST_PP_OVERLOAD(FUNC,__VA_ARGS__)(__VA_ARGS__),BOOST_PP_EMPTY())         \
)
#endif

#define DOME_New(...)                                                   DOME_PP_OVERLOAD(DOME_New, __VA_ARGS__)