#pragma once
#include "Logger.h"

namespace Log
{
	void Error(const std::string& msg);
	void Warning(const std::string& msg);
	void Info(const std::string& msg);
	void Debug(const std::string& msg);

	struct LoggerGetter
	{
		inline static Logger logger;
	};

	Logger& GetLogger();
}
