/*
filename:       typedef.h
author:         Raven
date created:   2023-08-25
description:
*/

#pragma once

#include "defines.h"

RAVEN_NAMESPACE_BEGIN

typedef int8_t              S8;
typedef uint8_t             U8;
typedef int16_t             S16;
typedef uint16_t            U16;
typedef int32_t             S32;
typedef uint32_t            U32;
typedef int64_t             S64;
typedef uint64_t            U64;
typedef U8                  Bool;
typedef float               F32;
typedef double              D64;
#if RCFG_USE_CHAR8_T
typedef char8_t             U8Char;
#else
typedef U8                  U8Char;
#endif
typedef char16_t            U16Char;
typedef char32_t            U32Char;
typedef char                Char;
typedef wchar_t             WChar;

#if RAVENCFG_IS_32BIT
typedef S32                 Int;
typedef U32                 Uint;
#define R_UINT_MAX			0xFFffFFff
#elif RAVENCFG_IS_64BIT
typedef S64                 Int;
typedef U64                 Uint;
#define R_UINT_MAX			0xFFffFFffFFffFFff
#else
typedef S32                 Int;
typedef U32                 Uint;
#define R_UINT_MAX			0xFFffFFff
#endif

typedef Uint                UintPtr;
typedef Int                 IntPtr;

typedef std::size_t         StdSize;        // don't use it unless it must be used (work with std library std::align for example)

typedef std::chrono::system_clock                               RClock;
typedef std::chrono::time_point<RClock, RClock::duration>       RTimePoint;

typedef std::chrono::high_resolution_clock                      RClockHR;
typedef std::chrono::time_point<RClockHR, RClockHR::duration>   RTimePointHR;

template<typename Rep, typename Period = std::ratio<1>>
using TDuration = std::chrono::duration<Rep, Period>;

typedef TDuration<S64, std::ratio<1, 1>>                        RSecond;
typedef TDuration<S64, std::ratio<1, 1000>>                     RMilliSecond;
typedef TDuration<S64, std::ratio<1, 1000000>>                  RMicroSecond;
typedef TDuration<S64, std::ratio<1, 1000000000>>               RNanoSecond;

typedef TDuration<D64, std::ratio<1, 1>>                        RSecondd;
typedef TDuration<D64, std::ratio<1, 1000>>                     RMilliSecondd;
typedef TDuration<D64, std::ratio<1, 1000000>>                  RMicroSecondd;
typedef TDuration<D64, std::ratio<1, 1000000000>>               RNanoSecondd;

RAVEN_NAMESPACE_END