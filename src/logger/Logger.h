#pragma once
#include <string>
#include <fstream>

namespace Log
{
	enum class ELevel : int
	{
		Error = 0,
		Warning,
		Info,
		Debug,
	};

	std::ostream& operator<<(std::ostream& os, ELevel level);

	class Logger
	{
	public:
		Logger();

		void log(ELevel level, const std::string& msg);

		ELevel getLogLevel() const;
		void setLogLevel(ELevel level);

	private:
		void logToFile(const std::string& msg);

		ELevel _currentLevel;
		std::ofstream _fileStream;
	};
}
