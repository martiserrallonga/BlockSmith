#pragma once
#include "Context.h"
#include "Renderer.h"
#include "Window.h"

#include "Menu.h"
#include "Scene.h"


namespace Engine
{
	class GameEngine
	{
	public:
		bool initialize();

		bool handleEvents();
		void update();
		void render();

		Window& getWindow();
		Renderer& getRenderer();
		Scene& getScene();

		void loadFont() const;

	private:
		Window _window;
		Renderer _renderer;

		Menu _menu;
		Scene _scene;
	};
}
