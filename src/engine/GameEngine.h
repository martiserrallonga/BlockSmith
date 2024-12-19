#pragma once
#include "Renderer.h"
#include "Scene.h"
#include "Settings.h"
#include "Window.h"


namespace Engine
{
	class GameEngine
	{
	public:
		bool initialize();

		bool handleEvents() const;
		void update();
		void render();
		void renderImGui();

		Window& getWindow();
		Renderer& getRenderer();
		Scene& getScene();

		void loadFont() const;

	private:
		Window _window;
		Renderer _renderer;

		Settings _settings;
		Scene _scene;
	};
}
