#pragma once
#include "LoggerGetter.h"
#include <nlohmann/json.hpp>

#include <fstream>


namespace Const {
	const std::string BasePath = "./config/";
}

// template <typename TJson, std::enable_if<nlohmann::detail::is_basic_json<TJson>::type>>
// template <typename TOrder>
class Json
{
public:
	Json() = default;

	static Json Parse(const std::string& path) {
		if (path.empty()) {
			Log::Error("Empty json path.");
			return {};
		}

		Json json;
		json.parse(path);
		return json;
	}

	void parse(std::string path) {
		std::ifstream file(Const::BasePath + path);
		if (!file.is_open()) {
			Log::Error(std::format("Config file {} not found.", path));
			return;
		}

		_json = nlohmann::json::parse(file);
		_path = std::move(path);
	}

	bool isValid() {
		if (_json.is_null()) {
			Log::Error(std::format("Invalid JSON file in path {}.", _path));
			return false;
		}

		if (_json.empty()) {
			Log::Error(std::format("Empty JSON file in path {}.", _path));
			return false;
		}

		return true;
	}

	template <typename T>
	T get(const std::string& key, T defaultValue) {
		if (!isValid()) return {};
		return _json.value(key, defaultValue);
	}

	template <typename T>
	T get(const std::string& key) requires (!std::same_as<T, Json>) {
		if (!isValid()) return {};
		if (!_json.contains(key)) {
			Log::Error(std::format("Key '{}' not found in path '{}'.", key, _path));
			return {};
		}
		return _json.at(key).get<T>();
	}

	Json get(const std::string& key) {
		if (!isValid()) return {};
		if (!_json.contains(key) || !_json.at(key).is_object()) {
			Log::Error(std::format("Key '{}' doesn't contain a json object.", key));
			return {};
		}
		return Json(_json.at(key));
	}

	std::string getPath() {
		return _path;
	}

private:
	explicit Json(nlohmann::json json)
		: _json(std::move(json)) {}

	std::string _path;
	nlohmann::json _json;
	//nlohmann::basic_json<TOrder> _json;
};

