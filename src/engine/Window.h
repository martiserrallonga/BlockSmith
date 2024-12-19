#pragma once
#include <SDL.h>

#include <functional>
#include <map>
#include <memory>
#include <string>


class Window
{
public:
	Window() = default;
	explicit Window(std::string configFile);

	SDL_Window* get() const;
	SDL_Point getSize() const;

	void processEvent(const SDL_WindowEvent& windowEvent) const;
	void addShownListener(std::string key, std::function<void(int, int)> callback);
	void addResizedListener(std::string key, std::function<void(int, int)> callback);

	bool operator!() const;

private:
	struct WindowDestroyer
	{
		void operator()(SDL_Window* window) const;
	};

	std::unique_ptr<SDL_Window, WindowDestroyer> _window;
	std::map<std::string, std::function<void(int, int)>> _shownListeners;
	std::map<std::string, std::function<void(int, int)>> _resizeListeners;
};
