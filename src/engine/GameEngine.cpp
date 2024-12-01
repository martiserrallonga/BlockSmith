#include "GameEngine.h"

#include "LoggerGetter.h"

#include <imgui_impl_sdl2.h>
#include <nlohmann/json.hpp>

#include <format>


bool Engine::GameEngine::initialize() {
	_window = Window("./config/window.json");
	if (!_window) {
		Log::Error(std::format("SDL Window initialization failed: {}", SDL_GetError()));
		return false;
	}

	_renderer = Renderer(_window, "./config/renderer.json");
	if (!_renderer) {
		Log::Error(std::format("SDL Renderer initialization failed."));
		return false;
	}

	Context::init(_window, _renderer);

	_scene = Scene();
	_menu = Menu();

	_window.addShownListener("Scene", [this](int width, int height) {
		getScene().onWindowShown(width, height);
		});

	_window.addResizedListener("Scene", [this](int width, int height) {
		getScene().onWindowResized(width, height);
		});

	return true;
}

void Engine::GameEngine::loadFont() const {}

bool Engine::GameEngine::handleEvents() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		ImGui_ImplSDL2_ProcessEvent(&e);
		if (e.type == SDL_QUIT) return false;
		if (e.type == SDL_WINDOWEVENT) {
			_window.processEvent(e.window);
		}
	}

	return true;
}

void Engine::GameEngine::update() {
	_scene.update();
}

void Engine::GameEngine::render() {
	_scene.render();
	_menu.render();

	SDL_RenderPresent(_renderer.get());
}

Window& Engine::GameEngine::getWindow() {
	return _window;
}

Renderer& Engine::GameEngine::getRenderer() {
	return _renderer;
}

Scene& Engine::GameEngine::getScene() {
	return _scene;
}

