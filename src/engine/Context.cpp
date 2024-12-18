#include "Context.h"

#include "Renderer.h"
#include "Window.h"
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>


void Context::init(const Window& window, const Renderer& renderer)
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Game pad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForSDLRenderer(window.get(), renderer.get());
	ImGui_ImplSDLRenderer2_Init(renderer.get());
}
