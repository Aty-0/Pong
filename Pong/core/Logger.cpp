#include "logger.h"

#include <filesystem>
#include <cstdarg> 

#pragma warning(disable:4996)

// TODO: macro ifdef windows

#include <windows.h>

#define VA_LIST_OUTPUT(buffer) 	va_list args; \
		va_start(args, text); \
		std::vsnprintf(buffer, sizeof(buffer), text, args); \
		va_end(args);	\

namespace sbt
{
	
	Logger::Logger() : m_linecount(0), m_log_file(), m_level()
	{
		m_level = Logger::Level::VERB;

		createLogFile();
	}

	Logger::~Logger()
	{
		m_log_file.close();
	}

	const char* Logger::parseArgsToString(const char* text, ...)
	{
		const auto BUFFER_SIZE = 2048;
		char buffer[BUFFER_SIZE];
		VA_LIST_OUTPUT(buffer);

		return buffer;
	}

	std::string Logger::getTime(bool printMinAndSec)
	{
		const auto _time = time(0);
		const auto localTime = localtime(&_time);

		const char* textparsed = printMinAndSec == true ?
			parseArgsToString("%i.%i.%i %i.%i.%i", (1900 + localTime->tm_year), (1 + localTime->tm_mon), localTime->tm_mday, localTime->tm_hour, localTime->tm_min, localTime->tm_sec) :
			parseArgsToString("%i.%i.%i", (1900 + localTime->tm_year), (1 + localTime->tm_mon), localTime->tm_mday);

		return textparsed;
	}

	void Logger::createLogFile()
	{
		// Create folder "Logs" if it's not exist
		if (!std::filesystem::is_directory("Logs") || !std::filesystem::exists("Logs"))
		{
			if (!std::filesystem::create_directory("Logs"))
			{
				throw std::runtime_error("Can't create directory");
			}
		}

		auto name = std::string();

		// set name for log file
		name.append("Log-");
		name.append(getTime(true));
		name.append(".log");

		m_log_file_path = "Logs/" + name;
		m_log_file = std::ofstream(m_log_file_path, std::ios_base::app);

		if (!m_log_file)
		{
			return;
		}

		m_log_file << "Log file\n\n";
		m_log_file.close();
	}

	const char* Logger::getLevelStr(Logger::Level level) const
	{
		switch (level)
		{
		case Logger::Level::INFO:
			return "Info";
		case Logger::Level::VERB:
			return "Verbose";
		case Logger::Level::ERR:
			return "Error";
		case Logger::Level::FATAL:
			return "Fatal";
		case Logger::Level::WARN:
			return "Warning";
		default:
			return "Unknown";
		}

		return "";
	}

	void Logger::print(Logger::Level level, const char* text, ...)
	{
		if (m_level > level)
			return;
		// Open log file 
		m_log_file = std::ofstream(m_log_file_path, std::ios_base::app);

		if (!m_log_file)
		{
			return;
		}

		char buffer[2048];
		VA_LIST_OUTPUT(buffer);

		auto line = std::string();
		// Print line count
		line.append("[" + std::to_string(m_linecount) + "] ");

		// Add to line corrent time
		line.append(getTime(false));

		// Add type and text from buffer
		auto message = " [" + std::string(getLevelStr(level)) + "]  " + std::string(buffer) + "\n";
		line.append(message);

		// Add current line to log file
		m_log_file << line;
		m_log_file.close();

		// Add line 
		m_linecount++;

		// If we are have debuging output
		OutputDebugString(line.c_str());
		printf(line.c_str());

		line.clear();
		memset(buffer, 0, sizeof(buffer));

		// trigger exception if it fatal error
		if (level == Logger::Level::FATAL)
		{
			throw std::runtime_error(std::string(buffer));
		}
	}
}