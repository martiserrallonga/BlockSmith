#pragma once
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
		void reloadWindow();
		void renderInMenu();

		Renderer& getRenderer();
		Scene& getScene();

		void loadFont() const;

	private:
		struct ConfigData final : Json, IConfigData
		{
			std::string windowPath;
			std::string rendererPath;

			void read(Json configJson) override;
			void save() override {}
		};

		ConfigData _configData;

		Window _window;
		Renderer _renderer;

		Menu _menu;
		Scene _scene;
	};
}
