#pragma once

#include <SDL.h>

#include <memory>
#include <string>

#include "IConfigData.h"


class Window
{
public:
	Window() = default;
	explicit Window(Json configJson);

	[[nodiscard]] SDL_Window* get() const;

	void renderInMenu();
	void saveConfig();

	bool operator!() const;

private:
	struct ConfigData final : IConfigData
	{
		std::string title;
		int width = 0;
		int height = 0;

		bool initFlagTimer = false;
		bool initFlagAudio = false;
		bool initFlagVideo = false;
		bool initFlagJoystick = false;
		bool initFlagHaptic = false;
		bool initFlagGameController = false;
		bool initFlagEvents = false;
		bool initFlagSensor = false;

		bool createFlagFullscreen = false;
		bool createFlagOpenGl = false;
		bool createFlagShown = false;
		bool createFlagHidden = false;
		bool createFlagBorderless = false;
		bool createFlagResizable = false;
		bool createFlagMinimized = false;
		bool createFlagMaximized = false;
		bool createFlagMouseGrabbed = false;
		bool createFlagInputFocus = false;
		bool createFlagMouseFocus = false;
		bool createFlagFullscreenDesktop = false;
		bool createFlagForeign = false;
		bool createFlagAllowHighDpi = false;
		bool createFlagMouseCapture = false;
		bool createFlagAlwaysOnTop = false;
		bool createFlagSkipTaskbar = false;
		bool createFlagUtility = false;
		bool createFlagTooltip = false;
		bool createFlagPopupMenu = false;
		bool createFlagKeyboardGrabbed = false;
		bool createFlagVulkan = false;
		bool createFlagMetal = false;

		void read(Json configJson) override;
		void save() override;

		Uint32 getInitFlags() const;
		Uint32 getCreateFlags() const;

		Json json;
	};

	struct WindowDestroyer
	{
		void operator()(SDL_Window* window) const;
	};

	ConfigData _configData;
	std::unique_ptr<SDL_Window, WindowDestroyer> _window;
};
