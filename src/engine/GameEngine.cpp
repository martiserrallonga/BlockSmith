#include "GameEngine.h"

#include "Context.h"
#include "LoggerGetter.h"
#include <imgui_impl_sdl2.h>
#include <nlohmann/json.hpp>

#include <format>


namespace Engine
{
	bool GameEngine::initialize() {
		_window = Window("./config/window.json");
		if (!_window) {
			Log::Error(std::format("SDL Window initialization failed: {}.", SDL_GetError()));
			return false;
		}

		_renderer = Renderer(_window, "./config/renderer.json");
		if (!_renderer) {
			Log::Error(std::format("SDL Renderer initialization failed.")); // TODO: No SDL_GetError here?
			return false;
		}

		Context::init(_window, _renderer);

		_scene = Scene();
		_settings = Settings();

		_window.addShownListener("Scene", [this](const int width, const int height) {
			getScene().onWindowShown(width, height);
			});

		_window.addResizedListener("Scene", [this](const int width, const int height) {
			getScene().onWindowResized(width, height);
			});

		return true;
	}

	// ReSharper disable once CppMemberFunctionMayBeStatic
	void GameEngine::loadFont() const {}

	bool GameEngine::handleEvents() const {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			ImGui_ImplSDL2_ProcessEvent(&event);
			if (event.type == SDL_QUIT) return false;
			if (event.type == SDL_WINDOWEVENT) {
				_window.processEvent(event.window);
			}
		}

		return true;
	}

	void GameEngine::update() {
		_scene.update();
	}

	void GameEngine::render() {
		_scene.render();
		_settings.renderImGui();

		SDL_RenderPresent(_renderer.get());
	}

	// ReSharper disable once CppMemberFunctionMayBeStatic
	void GameEngine::renderImGui() {}

	Window& GameEngine::getWindow() {
		return _window;
	}

	Renderer& GameEngine::getRenderer() {
		return _renderer;
	}

	Scene& GameEngine::getScene() {
		return _scene;
	}
}
