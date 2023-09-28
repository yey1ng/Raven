/*
filename:       define.h
author:         Raven
date created:   2023-08-25
description:
*/

#pragma once

#include <iostream>

// all external headers will be included here, make it as little as possible
#include <cstdint>                            // for int8_t, int16_t ......
#include <cstddef>
#include <ctime>
// all stl headers will be included here, make it as little as possible
#include <utility>                            // for std::move
#include <cstdarg>                           // for variable function parameters
#include <atomic>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <chrono>
#include <random>
#include <limits>
#include <functional>
#include <optional>
#include <vector>
#include <array>

#include "configuration_core.h"

#ifndef R_NULL
#define R_NULL  nullptr
#endif

#ifndef R_TRUE
#define R_TRUE 1
#endif

#ifndef R_FALSE
#define R_FALSE 0
#endif

#define R_BOOL(exp)						((exp) ? R_TRUE : R_FALSE)

#define R_SUCC(dr)                      ((dr) <= DOME_NS::DR::R_SUCCESS)
#define R_FAIL(dr)                      ((dr) > DOME_NS::DR::R_SUCCESS)

#define R_OVERRIDE						override

#define RAVEN_NAMESPACE_BEGIN			namespace raven{
#define RAVEN_NAMESPACE_END				}
#define RAVEN_NS_BEGIN(name)			namespace name{
#define RAVEN_NS_END(name)				}
#define RAVEN_NS						raven

// unicode tool macro defines
// TODO: remove type cast for u8 when c++ 20 is adopted (it isn't compatible with char type when use type cast, for example, R_U8('a'))
#define R_U8(str)						((const RAVEN_NS::U8Char*)u8##str)
#define R_U16(str)						(u##str)
#define R_U32(str)						(U##str)

#define R_C(str)						(str)
#define R_WC(str)						(L##str)

#define RAVEN_WIDEN2(x)                 R_WC(x)
#define RAVEN_WIDEN(x)                  RAVEN_WIDEN2(x)
#define RAVEN_WFILENAME                 RAVEN_WIDEN(__FILE__)

#define RAVEN_PP_OVERLOAD(FUNC, ...)                                                        \
BOOST_PP_IF(                                                                                \
    BOOST_PP_IS_EMPTY(__VA_ARGS__),                                                         \
    FUNC##0(),                                                                              \
    BOOST_PP_CAT(BOOST_PP_OVERLOAD(FUNC,__VA_ARGS__)(__VA_ARGS__),BOOST_PP_EMPTY())         \
)

/// Macro to declare the object class name.
#define RAVEN_OBJECT(class_)                                \
public:                                                     \
    const RAVEN_NS::U8Char* getClassName() const override   \
    {                                                       \
        return #class_;                                     \
    }