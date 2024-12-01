#include "Window.h"

#include "LoggerGetter.h"

#include <nlohmann/json.hpp>

#include <format>
#include <fstream>

Window::Window(std::string configFile) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
		Log::Error(std::format("SDL initialization failed: {}", SDL_GetError()));
		return;
	}

	// From 2.0.18: Enable native IME.
#ifdef SDL_HINT_IME_SHOW_UI
	SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

	std::ifstream file(configFile);
	if (!file.is_open()) {
		Log::Error(std::format("Config file {} not found", configFile));
		return;
	}
	nlohmann::json configJson = nlohmann::json::parse(file);

	const std::string title = configJson.at("title");
	const int width = configJson.at("width");
	const int height = configJson.at("height");

	constexpr auto flags = static_cast<SDL_WindowFlags>(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	_window.reset(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags));
}

SDL_Window* Window::get() const {
	return _window.get();
}

SDL_Point Window::getSize() const
{
	int width;
	int height;
	SDL_GetWindowSize(_window.get(), &width, &height);
	return { width, height };
}

void Window::processEvent(const SDL_WindowEvent& windowEvent) const {
	if (windowEvent.windowID != SDL_GetWindowID(_window.get())) {
		return;
	}

	if (windowEvent.event == SDL_WINDOWEVENT_CLOSE) {
		return;
	}
	else if (windowEvent.event == SDL_WINDOWEVENT_SHOWN) {
		auto size = getSize();
		for (const auto& [key, listener] : _shownListeners) {
			listener(size.x, size.y);
		}
	}
	else if (windowEvent.event == SDL_WINDOWEVENT_RESIZED) {
		auto size = getSize();
		for (const auto& [key, listener] : _resizeListeners) {
			listener(size.x, size.y);
		}
	}
}

void Window::addShownListener(std::string key, std::function<void(int, int)> callback) {
	_shownListeners.try_emplace(key, callback);
}

void Window::addResizedListener(std::string key, std::function<void(int, int)> callback) {
	_resizeListeners.try_emplace(key, callback);
}

bool Window::operator!() const {
	return !_window;
}

void Window::WindowDestroyer::operator()(SDL_Window* window) const {
	SDL_DestroyWindow(window);
	SDL_Quit();
}
