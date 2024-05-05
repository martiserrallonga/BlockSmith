#pragma once

#include <imgui.h>
#include <SDL.h>

#include <memory>
#include <string>


class Window;

class Renderer
{
public:
	Renderer() = default;
	Renderer(const Window& window, const std::string& configFile);

	[[nodiscard]] SDL_Renderer* get() const;

	void setColor(const ImColor& color) const;

	bool operator!() const;

private:
	struct RendererDestroyer
	{
		void operator()(SDL_Renderer* renderer) const;
	};

	std::unique_ptr<SDL_Renderer, RendererDestroyer> _renderer;
};
