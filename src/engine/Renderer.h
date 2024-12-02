#pragma once

#include "IConfigData.h"

#include <imgui.h>
#include <nlohmann/json.hpp>
#include <SDL.h>

#include <memory>


class Window;

class Renderer
{
public:
	Renderer() = default;
	Renderer(const Window& window, Json configJson);

	[[nodiscard]] SDL_Renderer* get() const;

	void setColor(const ImColor& color) const;

	void renderInMenu();

	bool operator!() const;

private:
	struct ConfigData final : Json, IConfigData
	{
		bool flagSoftware = false;
		bool flagAccelerated = false;
		bool flagPresentVSync = false;
		bool flagTargetTexture = false;

		void read(Json configJson) override;
		void save() override {}
	};

	struct RendererDestroyer
	{
		void operator()(SDL_Renderer* renderer) const;
	};

	ConfigData _configData;
	std::unique_ptr<SDL_Renderer, RendererDestroyer> _renderer;
};
