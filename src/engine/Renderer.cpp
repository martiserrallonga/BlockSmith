#include "Renderer.h"

#include "LoggerGetter.h"
#include "Window.h"

#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <nlohmann/json.hpp>


Renderer::Renderer(const Window& window, Json configJson) {
	_configData.read(configJson);

	Uint32 flags = 0U;
	flags |= _configData.flagSoftware ? SDL_RENDERER_SOFTWARE : 0U;
	flags |= _configData.flagAccelerated ? SDL_RENDERER_ACCELERATED : 0U;
	flags |= _configData.flagPresentVSync ? SDL_RENDERER_PRESENTVSYNC : 0U;
	flags |= _configData.flagTargetTexture ? SDL_RENDERER_TARGETTEXTURE : 0U;

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

void Renderer::renderInMenu() {
	ImGui::Checkbox("Software", &_configData.flagSoftware);
	ImGui::SameLine();
	ImGui::Checkbox("Accelerated", &_configData.flagAccelerated);
	//ImGui::SameLine();
	ImGui::Checkbox("VSync", &_configData.flagPresentVSync);
	ImGui::SameLine();
	ImGui::Checkbox("Target Texture", &_configData.flagTargetTexture);
}

bool Renderer::operator!() const {
	return !_renderer;
}

void Renderer::ConfigData::read(Json configJson) {
	auto flags = configJson.get<nlohmann::json>("flags");

	auto flagsJson = configJson.getJson("flags");
	//flagSoftware = flagsJson.get("SDL_RENDERER_SOFTWARE", false);
	//flagAccelerated = flagsJson.get("SDL_RENDERER_ACCELERATED", true);
	//flagPresentVSync = flagsJson.get("SDL_RENDERER_PRESENT_VSYNC", true);
	//flagTargetTexture = flagsJson.get("SDL_RENDERER_TARGET_TEXTURE", false);
}

void Renderer::RendererDestroyer::operator()(SDL_Renderer* renderer) const {
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_DestroyRenderer(renderer);
}
