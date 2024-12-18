#include "Renderer.h"

#include "Window.h"
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>


Renderer::Renderer(const Window& window, std::string configPath)
	: _configData(std::move(configPath))
{
	_configData.load();

	Uint32 flags = 0;
	flags |= _configData.flagSoftware ? SDL_RENDERER_SOFTWARE : 0;
	flags |= _configData.flagAccelerated ? SDL_RENDERER_ACCELERATED : 0;
	flags |= _configData.flagPresentVSync ? SDL_RENDERER_PRESENTVSYNC : 0;
	flags |= _configData.flagTargetTexture ? SDL_RENDERER_TARGETTEXTURE : 0;

	_renderer.reset(SDL_CreateRenderer(window.get(), -1, flags));
}

SDL_Renderer* Renderer::get() const {
	return _renderer.get();
}

void Renderer::setColor(const ImColor& color) const {
	SDL_SetRenderDrawColor(_renderer.get(),
		static_cast<Uint8>(color.Value.x * 255),
		static_cast<Uint8>(color.Value.y * 255),
		static_cast<Uint8>(color.Value.z * 255),
		static_cast<Uint8>(color.Value.w * 255)
	);
}

bool Renderer::operator!() const {
	return !_renderer;
}

void Renderer::RendererDestroyer::operator()(SDL_Renderer* renderer) const {
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_DestroyRenderer(renderer);
}
