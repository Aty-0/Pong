#pragma once
#include "common.h"

namespace sbt
{
	class Logger : public sbt::Singleton<Logger>
	{
	public:
		enum Level
		{
			NONE = 0,
			VERB,
			INFO,
			WARN,
			ERR,
			FATAL,
		};

		Logger();
		~Logger();

		void				print(Logger::Level level, const char* text, ...);
		void				createLogFile();
	private:
		inline const char* getLevelStr(Logger::Level level) const;
		// simple parsing of args to string 
		inline const char* parseArgsToString(const char* text, ...);

		// get current time in string 
		inline std::string	getTime(bool printMinAndSec);

		std::uint32_t	m_linecount;
		std::ofstream	m_log_file;
		Level		m_level;
		std::string	m_log_file_path;

		bool				m_scroll_to_bottom;
	};
	
	// quick access to logger
	inline const auto log = sbt::Logger::getInstance();
}


#define INFO(msg, ...) \
do \
{ \
	 sbt::log->print(sbt::Logger::Level::INFO, msg, ##__VA_ARGS__); \
} \
while(0)

#define VERB(msg, ...) \
do \
{ \
	  sbt::log->print(sbt::Logger::Level::VERB, msg, ##__VA_ARGS__); \
} \
while(0)

#define WARN(msg, ...) \
do \
{ \
	  sbt::log->print(sbt::Logger::Level::WARN, msg, ##__VA_ARGS__); \
} \
while(0)

#define ERR(msg, ...) \
do \
{ \
	  sbt::log->print(sbt::Logger::Level::ERR, msg, ##__VA_ARGS__); \
} \
while(0)

#define FATAL(msg, ...) \
do \
{ \
	  sbt::log->print(sbt::Logger::Level::FATAL, msg, ##__VA_ARGS__); \
} \
while(0)
