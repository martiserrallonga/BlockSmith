#pragma once
#include <chrono>
#include <format>
#include <string>


namespace Clock
{
	inline std::string GetCurrentTime()
	{
		const auto now = std::chrono::system_clock::now();
		const auto time = std::chrono::current_zone()->to_local(now);
		return std::format("{:%Y-%m-%d %X}", time);
	}
}