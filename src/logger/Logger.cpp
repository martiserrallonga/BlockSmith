#include "Logger.h"

#include "Clock.h"

#include <iostream>


namespace Log
{
	std::ostream& operator<<(std::ostream& os, const ELevel level) {
		using enum ELevel;
		switch (level) {
		case Error: return os << "ERROR";
		case Warning: return os << "WARNING";
		case Info: return os << "INFO";
		case Debug: return os << "DEBUG";
		}
		return os << "UNDEFINED";
	}

	Logger::Logger() {
#if DEBUG
		_currentLevel = ELevel::Debug;
#else
		_currentLevel = ELevel::Warning;
#endif

		_fileStream.open("logs.txt");
	}

	void Logger::log(const ELevel level, const std::string& msg) {
		std::stringstream ss;
		ss <<
			'[' << level << ']' <<
			'[' << Clock::getCurrentTime() << ']' <<
			' ' << msg;

		if (level <= _currentLevel) {
			std::cout << ss.str() << '\n';
		}

		logToFile(ss.str());
	}

	ELevel Logger::getLogLevel() const {
		return _currentLevel;
	}

	void Logger::setLogLevel(const ELevel level) {
		_currentLevel = level;
	}

	void Logger::logToFile(const std::string& msg) {
		if (_fileStream.is_open()) {
			_fileStream << msg << "\n";
			_fileStream.flush();
		}
	}
}
