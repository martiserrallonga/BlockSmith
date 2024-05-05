#include "Renderer.h"

#include "Window.h"

#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

Renderer::Renderer(const Window& window, const std::string&) {
	_renderer.reset(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED));
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
