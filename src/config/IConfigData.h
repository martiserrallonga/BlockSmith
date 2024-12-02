#pragma once

#include "LoggerGetter.h"

#include <nlohmann/json.hpp>

#include <fstream>


//template <typename TJson, std::enable_if<nlohmann::detail::is_basic_json<TJson>::type>>
template <typename TOrder = <>>
class Json
{
public:
	Json() = default;
	explicit Json(nlohmann::json json) // private ??
		: _json(std::move(json)) {}

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
		std::ifstream file("./config/" + path);
		if (!file.is_open()) {
			Log::Error(std::format("Config file {} not found", path));
			return;
		}

		_json = nlohmann::json::parse(file);
		_path = std::move(path);
	}

	template <typename T>
	T get(std::string key, T defaultValue) {
		return _json.value(key, defaultValue);
	}

	template <typename T>
	T get(std::string key) {
		if (!_json.contains(key)) {
			Log::Error(std::format("Key '{}' not found in path '{}'", key, _path));
			return {};
		}
		return _json.at(key);
	}

	Json getJson(std::string key) {
		if (!_json.contains(key) || !_json.at(key).is_object()) {
			Log::Error(std::format("Key '{}' doesn't contain a json object", key));
			return {};
		}
		return Json(_json.at(key));
	}

	std::string getPath() {
		return _path;
	}

	template <typename T>
	void set(std::string key, T value) {
		_json[key] = value;
	}

	void set(const std::string& key, Json value) {
		_json[key] = std::move(value._json);
	}

	void save() {
		std::ofstream file("./config/" + _path);
		if (!file.is_open()) {
			Log::Error(std::format("Config file {} not found", _path));
			return;
		}

		file << _json;
	}

private:
	std::string _path;
	nlohmann::basic_json<TOrder> _json;
};

class IConfigData
{
public:
	virtual ~IConfigData() = default;
	virtual void read(Json<> configJson) = 0;
	virtual void save() = 0;
};
