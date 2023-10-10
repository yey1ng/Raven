/*
filename:       logger.h
author:         Raven
date created:   2023-08-25
description:
*/

#pragma once

#include <string>
#include "typedefs.h"

// Macros for quick access. File and line are added through the respective macros.
#define R_LOG_INFO(...) log(formatString(__VA_ARGS__), std::string(__FILE__), __LINE__, RAVEN_NS::INFO)
#define R_LOG_WARNING(...) log(formatString(__VA_ARGS__), std::string(__FILE__), __LINE__, RAVEN_NS::WARNING)
#define R_LOG_ERROR(...) log(formatString(__VA_ARGS__), std::string(__FILE__), __LINE__, RAVEN_NS::ERR)
#define R_LOG_FATAL(b, ...) if(!(b)) { log(formatString(__VA_ARGS__), std::string(__FILE__), __LINE__, RAVEN_NS::FATAL); }

RAVEN_NAMESPACE_BEGIN

enum LogLevel
{
	INFO = 0,
	WARNING = 1,
	ERR = 2,
	FATAL = 3
};

enum LogVerbosity
{
	VERBOSITY_BASIC = 0x00,
	VERBOSITY_TIMESTAMP = 0x01,
	VERBOSITY_LEVEL = 0x02,
	VERBOSITY_FILE = 0x04,
	VERBOSITY_LINE = 0x08,
	VERBOSITY_ALL = 0x0f
};

// Custom stream callback type. Use to implement your own logging stream such as through a network etc.
typedef void (*CustomStreamCallback)(std::string, LogLevel);

extern void initialize();
extern void setVerbosity(int flags);

// Open streams.
extern void openFileStream();
extern void openConsoleStream();
extern void openCustomStream(CustomStreamCallback callback);

// Close streams.
extern void closeFileStream();
extern void closeConsoleStream();
extern void closeCustomStream();

// Debug mode. These will flush the stream immediately after each log.
extern void enableDebugMode();
extern void disableDebugMode();

// Main log method. File, line and level are required in addition to log message.
extern void log(std::string text, std::string file, int line, LogLevel level);

// Simplified API.
extern void logInfo(std::string text);
extern void logError(std::string text);
extern void logWarning(std::string text);
extern void logFatal(std::string text);

// Explicitly flush all streams.
extern void flush();

RAVEN_NAMESPACE_END