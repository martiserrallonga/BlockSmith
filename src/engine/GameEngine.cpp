#include "GameEngine.h"

#include "Context.h"
#include "LoggerGetter.h"

#include <imgui_impl_sdl2.h>
#include <imgui_stdlib.h>
#include <nlohmann/json.hpp>

#include <format>


bool Engine::GameEngine::initialize() {
	_configData.read(Json::Parse("engine.json"));

	_window = Window(Json::Parse(_configData.windowPath));
	if (!_window) {
		Log::Error(std::format("SDL Window initialization failed: {}", SDL_GetError()));
		return false;
	}

	_renderer = Renderer(_window, Json::Parse(_configData.rendererPath));
	if (!_renderer) {
		Log::Error(std::format("SDL Renderer initialization failed.", SDL_GetError()));
		return false;
	}

	Context::init(_window, _renderer);

	_scene = Scene();
	_menu = Menu();

	return true;
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

void Engine::GameEngine::reloadWindow()
{
	Log::Debug("Reload Window");
	_window.saveConfig();
}


void Engine::GameEngine::renderInMenu() {
	if (!ImGui::TreeNode("Config")) return;




	//static std::string staticStr = "Hello world!";
	//ImGui::InputText("Hello", &staticStr);

	//ImGui::BeginCombo("Window", )

	//std::string("Window: " + _configData.getPath()).c_str())) {
	if (ImGui::TreeNode("Window")) {
		std::string windowPath = _configData.windowPath;
		//ImGui::Text("windows config: %s", _configData.windowPath.c_str());
		//if (ImGui::InputText("Change Path", &windowPath, ImGuiInputTextFlags_EnterReturnsTrue)) {
		//	if (ImGui::IsItemEdited()) {
		//		Log::Debug(std::format("Input Text: {}", windowPath));
		//	}
		//}

		//static float  width = 150.f;
		//ImGui::DragFloat("Width", &width);

		ImGui::Text("Path:");
		ImGui::SameLine();
		ImGui::PushItemWidth(150.f);
		if (ImGui::InputText("", &windowPath, ImGuiInputTextFlags_EnterReturnsTrue)) {
			Log::Debug(std::format("Input Text: {}", windowPath));
		}
		ImGui::PopItemWidth();

		ImGui::SameLine();

		const auto reloadColor = static_cast<ImVec4>(ImColor{ 100, 100, 100, 255 });
		ImGui::PushStyleColor(ImGuiCol_Button, reloadColor);
		ImGui::SmallButton("Reload");
		if (ImGui::IsItemClicked()) {
			reloadWindow();
		}
		ImGui::PopStyleColor();

		_window.renderInMenu();
		ImGui::TreePop();
	}

	ImGui::TreePop();

	//ImGui::Text("%s", std::string("renderer config: " + _configData.rendererPath).c_str());
	//_renderer.renderInMenu();
}

Renderer& Engine::GameEngine::getRenderer() {
	return _renderer;
}

Scene& Engine::GameEngine::getScene() {
	return _scene;
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

void Engine::GameEngine::ConfigData::read(Json configJson) {
	windowPath = configJson.get<std::string>("window_path");
	rendererPath = configJson.get<std::string>("renderer_path");
}