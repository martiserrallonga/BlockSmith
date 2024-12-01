#include "Menu.h"

#include "EngineGetter.h"
#include "LoggerGetter.h"

#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>


Menu::Menu() {
	_logLevel = DropdownValue(
		"Log Level",
		{ "Error", "Warning", "Info", "Debug" },
		static_cast<int>(Log::GetLogger().getLogLevel()),
		[](int level) {
			const auto enumLevel = static_cast<Log::ELevel>(level);
			auto& logger = Log::GetLogger();
			logger.setLogLevel(enumLevel);
			logger.log(enumLevel, "Log level changed!");
		});
}

void Menu::render() {
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Inspector");

	const ImGuiIO& io = ImGui::GetIO();
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

	ImGui::Checkbox("Demo Window", &_showDemoWindow);
	if (_showDemoWindow) ImGui::ShowDemoWindow(&_showDemoWindow);

	_logLevel.renderInMenu();

	Engine::Get().getScene().renderInMenu();

	ImGui::End();

	ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}
