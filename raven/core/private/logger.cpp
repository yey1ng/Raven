/*
filename:       logger.cpp
author:         Raven
date created:   2023-08-25
description:
*/

#include <core/public/logger.h>

#include <chrono>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <mutex>

#define FILE_STREAM_INDEX 0
#define CONSOLE_STREAM_INDEX 1
#define CUSTOM_STREAM_INDEX 2

#define LOG_SEPERATOR                                                            \
    "**************************************************************************" \
    "******************************\n"

RAVEN_NAMESPACE_BEGIN

struct LoggerState
{
	bool					m_OpenStreams[3];
	std::mutex				m_LogMutex;
	std::ofstream			m_Stream;
	std::time_t				m_RawTime;
	std::tm*				m_TimeInfo;
	int						m_Verbosity;
	char					m_TempBuffer[80];
	CustomStreamCallback	m_Callback;
	bool					m_Debug;
};

LoggerState g_Logger;

void initialize()
{
	for (int i = 0; i < 3; i++)
		g_Logger.m_OpenStreams[i] = false;

	g_Logger.m_Callback = nullptr;
	g_Logger.m_Verbosity = VERBOSITY_ALL;
	g_Logger.m_Debug = false;
}

void setVerbosity(int flags) { g_Logger.m_Verbosity = flags; }

void openConsoleStream()
{
	g_Logger.m_OpenStreams[CONSOLE_STREAM_INDEX] = true;

	std::time(&g_Logger.m_RawTime);
	localtime_s(g_Logger.m_TimeInfo, &g_Logger.m_RawTime);
	std::strftime(g_Logger.m_TempBuffer, 80, "%H:%M:%S", g_Logger.m_TimeInfo);
	std::cout << LOG_SEPERATOR;
	std::cout << g_Logger.m_TempBuffer << "Log Started.\n";
	std::cout << LOG_SEPERATOR;
}

void openFileStream()
{
	g_Logger.m_OpenStreams[FILE_STREAM_INDEX] = true;
	g_Logger.m_Stream.open("log.txt", std::ios::app | std::ofstream::out);

	std::time(&g_Logger.m_RawTime);
	localtime_s(g_Logger.m_TimeInfo, &g_Logger.m_RawTime);
	std::strftime(g_Logger.m_TempBuffer, 80, "%H:%M:%S", g_Logger.m_TimeInfo);
	g_Logger.m_Stream << LOG_SEPERATOR;
	std::cout << g_Logger.m_TempBuffer << "Log Started.\n";
	g_Logger.m_Stream << LOG_SEPERATOR;
}

void openCustomStream(CustomStreamCallback callback)
{
	g_Logger.m_OpenStreams[CUSTOM_STREAM_INDEX] = true;
	g_Logger.m_Callback = callback;

	std::time(&g_Logger.m_RawTime);

	if (g_Logger.m_Callback)
	{
		g_Logger.m_Callback(LOG_SEPERATOR, INFO);

		localtime_s(g_Logger.m_TimeInfo, &g_Logger.m_RawTime);
		std::strftime(g_Logger.m_TempBuffer, 80, "%H:%M:%S", g_Logger.m_TimeInfo);
		std::string init_string = g_Logger.m_TempBuffer;
		init_string += "Log Started.\n";

		g_Logger.m_Callback(init_string, INFO);
		g_Logger.m_Callback(LOG_SEPERATOR, INFO);
	}
}

void closeConsoleStream()
{
	g_Logger.m_OpenStreams[CONSOLE_STREAM_INDEX] = false;

	std::time(&g_Logger.m_RawTime);
	localtime_s(g_Logger.m_TimeInfo, &g_Logger.m_RawTime);
	std::strftime(g_Logger.m_TempBuffer, 80, "%H:%M:%S", g_Logger.m_TimeInfo);
	std::cout << LOG_SEPERATOR;
	std::cout << g_Logger.m_TempBuffer << "Log Ended.\n";
	std::cout << LOG_SEPERATOR;
}

void closeFileStream()
{
	g_Logger.m_OpenStreams[FILE_STREAM_INDEX] = false;

	std::time(&g_Logger.m_RawTime);
	localtime_s(g_Logger.m_TimeInfo, &g_Logger.m_RawTime);
	std::strftime(g_Logger.m_TempBuffer, 80, "%H:%M:%S", g_Logger.m_TimeInfo);
	g_Logger.m_Stream << LOG_SEPERATOR;
	g_Logger.m_Stream << g_Logger.m_TempBuffer << "Log Ended.\n";
	g_Logger.m_Stream << LOG_SEPERATOR;

	g_Logger.m_Stream.close();
}

void closeCustomStream()
{
	g_Logger.m_OpenStreams[CUSTOM_STREAM_INDEX] = false;

	std::time(&g_Logger.m_RawTime);

	if (g_Logger.m_Callback)
	{
		g_Logger.m_Callback(LOG_SEPERATOR, INFO);

		localtime_s(g_Logger.m_TimeInfo, &g_Logger.m_RawTime);
		std::strftime(g_Logger.m_TempBuffer, 80, "%H:%M:%S", g_Logger.m_TimeInfo);
		std::string init_string = g_Logger.m_TempBuffer;
		init_string += "Log Ended.\n";

		g_Logger.m_Callback(init_string, INFO);
		g_Logger.m_Callback(LOG_SEPERATOR, INFO);
	}
}

void enableDebugMode() { g_Logger.m_Debug = true; }

void disableDebugMode() { g_Logger.m_Debug = false; }

void log(std::string text, std::string file, int line, LogLevel level)
{
	std::lock_guard<std::mutex> lock(g_Logger.m_LogMutex);

	std::string file_with_extension = file.substr(file.find_last_of("/\\") + 1);
	std::time(&g_Logger.m_RawTime);
	localtime_s(g_Logger.m_TimeInfo, &g_Logger.m_RawTime);
	std::strftime(g_Logger.m_TempBuffer, 80, "%H:%M:%S", g_Logger.m_TimeInfo);

	std::string log_level_string;

	switch (level)
	{
	case INFO:
	{
		log_level_string = "INFO	";
		break;
	}
	case WARNING:
	{
		log_level_string = "WARNING	";
		break;
	}
	case ERR:
	{
		log_level_string = "ERROR	";
		break;
	}
	case FATAL:
	{
		log_level_string = "FATAL	";
		break;
	}
	}

	std::string output;

	if ((g_Logger.m_Verbosity & VERBOSITY_TIMESTAMP) || (g_Logger.m_Verbosity & VERBOSITY_LEVEL))
	{
		output = "[ ";

		if (g_Logger.m_Verbosity & VERBOSITY_TIMESTAMP)
			output += g_Logger.m_TempBuffer;

		if ((g_Logger.m_Verbosity & VERBOSITY_TIMESTAMP) && (g_Logger.m_Verbosity & VERBOSITY_LEVEL))
			output += " | ";

		if (g_Logger.m_Verbosity & VERBOSITY_LEVEL)
			output += log_level_string;

		output += " ] : ";
	}

	output += text;

	if (g_Logger.m_Verbosity & VERBOSITY_FILE)
	{
		output += " , FILE : ";
		output += file_with_extension;
	}

	if (g_Logger.m_Verbosity & VERBOSITY_LINE)
	{
		output += " , LINE : ";
		output += std::to_string(line);
	}

	if (g_Logger.m_OpenStreams[FILE_STREAM_INDEX])
	{
		g_Logger.m_Stream << output << "\n";
	}

	if (g_Logger.m_OpenStreams[CONSOLE_STREAM_INDEX])
	{
		std::cout << output << "\n";
	}

	if (g_Logger.m_OpenStreams[CUSTOM_STREAM_INDEX] && g_Logger.m_Callback)
	{
		g_Logger.m_Callback(output, level);
	}

	// Flush stream if error
	if (level == ERR || level == FATAL || g_Logger.m_Debug)
		flush();
}

void logSimple(std::string text, LogLevel level)
{
	std::lock_guard<std::mutex> lock(g_Logger.m_LogMutex);

	std::time(&g_Logger.m_RawTime);
	localtime_s(g_Logger.m_TimeInfo, &g_Logger.m_RawTime);
	std::strftime(g_Logger.m_TempBuffer, 80, "%H:%M:%S", g_Logger.m_TimeInfo);

	std::string log_level_string;

	switch (level)
	{
	case INFO:
	{
		log_level_string = "INFO   ";
		break;
	}
	case WARNING:
	{
		log_level_string = "WARNING";
		break;
	}
	case ERR:
	{
		log_level_string = "ERROR  ";
		break;
	}
	case FATAL:
	{
		log_level_string = "FATAL  ";
		break;
	}
	}

	std::string output;

	if ((g_Logger.m_Verbosity & VERBOSITY_TIMESTAMP) || (g_Logger.m_Verbosity & VERBOSITY_LEVEL))
	{
		output = "[ ";

		if (g_Logger.m_Verbosity & VERBOSITY_TIMESTAMP)
			output += g_Logger.m_TempBuffer;

		if ((g_Logger.m_Verbosity & VERBOSITY_TIMESTAMP) && (g_Logger.m_Verbosity & VERBOSITY_LEVEL))
			output += " | ";

		if (g_Logger.m_Verbosity & VERBOSITY_LEVEL)
			output += log_level_string;

		output += " ] : ";
	}

	output += text;

	if (g_Logger.m_OpenStreams[FILE_STREAM_INDEX])
	{
		g_Logger.m_Stream << output << "\n";
	}

	if (g_Logger.m_OpenStreams[CONSOLE_STREAM_INDEX])
	{
		std::cout << output << "\n";
	}

	if (g_Logger.m_OpenStreams[CUSTOM_STREAM_INDEX] && g_Logger.m_Callback)
	{
		g_Logger.m_Callback(output, level);
	}
}

void logInfo(std::string text) { logSimple(text, INFO); }

void logError(std::string text) { logSimple(text, ERR); }

void logWarning(std::string text) { logSimple(text, WARNING); }

void logFatal(std::string text) { logSimple(text, FATAL); }

void flush()
{
	if (g_Logger.m_OpenStreams[FILE_STREAM_INDEX])
	{
		g_Logger.m_Stream.flush();
	}
}

RAVEN_NAMESPACE_END