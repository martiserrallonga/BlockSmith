#pragma once
#include <string>
#include <chrono>
#include <format>

namespace Clock
{
	inline std::string getCurrentTime()
	{
		const auto now = std::chrono::system_clock::now();
		const auto time = std::chrono::current_zone()->to_local(now);
		return std::format("{:%Y-%m-%d %X}", time);
	}
}