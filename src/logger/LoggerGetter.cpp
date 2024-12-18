#include "LoggerGetter.h"


namespace Log
{
	void Error(const std::string& msg) {
		GetLogger().log(ELevel::Error, msg);
	}

	void Warning(const std::string& msg) {
		GetLogger().log(ELevel::Warning, msg);
	}

	void Info(const std::string& msg) {
		GetLogger().log(ELevel::Info, msg);
	}

	void Debug(const std::string& msg) {
		GetLogger().log(ELevel::Debug, msg);
	}

	Logger& GetLogger() {
		return LoggerGetter::logger;
	}
}
