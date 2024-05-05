#pragma once

#include <SDL.h>

#include <memory>
#include <string>


class Window
{
public:
	Window() = default;
	explicit Window(std::string configFile);

	[[nodiscard]] SDL_Window* get() const;

	bool operator!() const;

private:
	struct WindowDestroyer
	{
		void operator()(SDL_Window* window) const;
	};

	std::unique_ptr<SDL_Window, WindowDestroyer> _window;
};
