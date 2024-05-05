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

	_renderer = Renderer(_window, "./config/renderer.json"); // TODO: renderer config
	if (!_renderer) {
		Log::Error(std::format("SDL Renderer initialization failed.")); // TODO: No SDL_GetError here?
		return false;
	}

	Context::init(_window, _renderer);

	_scene = Scene();
	_menu = Menu();

	return true;
}

void Engine::GameEngine::loadFont() const {
	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	// - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
	// - Read 'docs/FONTS.md' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	//io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
	//IM_ASSERT(font != nullptr);
}

bool Engine::GameEngine::handleEvents() {
	// Poll and handle events (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		ImGui_ImplSDL2_ProcessEvent(&e);
		if (e.type == SDL_QUIT) return false;
		if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE && e.window.windowID == SDL_GetWindowID(_window.get())) return false;
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

Renderer& Engine::GameEngine::getRenderer() {
	return _renderer;
}

Scene& Engine::GameEngine::getScene() {
	return _scene;
}

