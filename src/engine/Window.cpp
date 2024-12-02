#include "Window.h"

#include "LoggerGetter.h"

#include <nlohmann/json.hpp>

#include <format>

#include "imgui.h"

Window::Window(Json configJson) {

	_configData.read(configJson);

	if (SDL_Init(_configData.getInitFlags())) {
		Log::Error(std::format("SDL initialization failed: {}", SDL_GetError()));
		return;
	}

	// From 2.0.18: Enable native IME.
#ifdef SDL_HINT_IME_SHOW_UI
	SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

	_window.reset(SDL_CreateWindow(
		_configData.title.c_str()
		, SDL_WINDOWPOS_CENTERED
		, SDL_WINDOWPOS_CENTERED
		, _configData.width
		, _configData.height
		, _configData.getCreateFlags()
	));
}

SDL_Window* Window::get() const {
	return _window.get();
}

void Window::renderInMenu() {
	ImGui::DragInt("Width", &_configData.width);
	ImGui::DragInt("Height", &_configData.height);
}

void Window::saveConfig() {
	_configData.save();
}

bool Window::operator!() const {
	return !_window;
}

void Window::ConfigData::read(Json configJson) {
	json = std::move(configJson);

	title = json.get<std::string>("title");
	width = json.get("width", 1280);
	height = json.get("height", 720);

	Json initFlags = json.getJson("init_flags");
	initFlagTimer = initFlags.get("SDL_INIT_TIMER", true);
	initFlagAudio = initFlags.get("SDL_INIT_AUDIO", false);
	initFlagVideo = initFlags.get("SDL_INIT_VIDEO", true);
	initFlagJoystick = initFlags.get("SDL_INIT_JOYSTICK", false);
	initFlagHaptic = initFlags.get("SDL_INIT_HAPTIC", false);
	initFlagGameController = initFlags.get("SDL_INIT_GAME_CONTROLLER", true);
	initFlagEvents = initFlags.get("SDL_INIT_EVENTS", false);
	initFlagSensor = initFlags.get("SDL_INIT_SENSOR", false);

	Json createFlags = json.getJson("create_flags");
	createFlagFullscreen = createFlags.get("SDL_WINDOW_FULLSCREEN", false);
	createFlagOpenGl = createFlags.get("SDL_WINDOW_OPENGL", false);
	createFlagShown = createFlags.get("SDL_WINDOW_SHOWN", false);
	createFlagHidden = createFlags.get("SDL_WINDOW_HIDDEN", false);
	createFlagBorderless = createFlags.get("SDL_WINDOW_BORDERLESS", false);
	createFlagResizable = createFlags.get("SDL_WINDOW_RESIZABLE", true);
	createFlagMinimized = createFlags.get("SDL_WINDOW_MINIMIZED", false);
	createFlagMaximized = createFlags.get("SDL_WINDOW_MAXIMIZED", false);
	createFlagMouseGrabbed = createFlags.get("SDL_WINDOW_MOUSE_GRABBED", false);
	createFlagInputFocus = createFlags.get("SDL_WINDOW_INPUT_FOCUS", false);
	createFlagMouseFocus = createFlags.get("SDL_WINDOW_MOUSE_FOCUS", false);
	createFlagFullscreenDesktop = createFlags.get("SDL_WINDOW_FULLSCREEN_DESKTOP", false);
	createFlagForeign = createFlags.get("SDL_WINDOW_FOREIGN", false);
	createFlagAllowHighDpi = createFlags.get("SDL_WINDOW_ALLOW_HIGH_DPI", true);
	createFlagMouseCapture = createFlags.get("SDL_WINDOW_MOUSE_CAPTURE", false);
	createFlagAlwaysOnTop = createFlags.get("SDL_WINDOW_ALWAYS_ON_TOP", false);
	createFlagSkipTaskbar = createFlags.get("SDL_WINDOW_SKIP_TASKBAR", false);
	createFlagUtility = createFlags.get("SDL_WINDOW_UTILITY", false);
	createFlagTooltip = createFlags.get("SDL_WINDOW_TOOLTIP", false);
	createFlagPopupMenu = createFlags.get("SDL_WINDOW_POPUP_MENU", false);
	createFlagKeyboardGrabbed = createFlags.get("SDL_WINDOW_KEYBOARD_GRABBED", false);
	createFlagVulkan = createFlags.get("SDL_WINDOW_VULKAN", false);
	createFlagMetal = createFlags.get("SDL_WINDOW_METAL", false);
}

void Window::ConfigData::save() {
	nlohmann::ordered_json outJson;
	outJson.set("title", title);
	outJson.set("width", width);
	outJson.set("height", height);

	Json initFlags;
	initFlags.set("SDL_INIT_TIMER", initFlagTimer);
	initFlags.set("SDL_INIT_AUDIO", initFlagAudio);
	initFlags.set("SDL_INIT_VIDEO", initFlagVideo);
	initFlags.set("SDL_INIT_JOYSTICK", initFlagJoystick);
	initFlags.set("SDL_INIT_HAPTIC", initFlagHaptic);
	initFlags.set("SDL_INIT_GAME_CONTROLLER", initFlagGameController);
	initFlags.set("SDL_INIT_EVENTS", initFlagEvents);
	initFlags.set("SDL_INIT_SENSOR", initFlagSensor);
	json.set("init_flags", initFlags);

	Json createFlags;
	createFlags.set("SDL_WINDOW_FULLSCREEN", createFlagFullscreen);
	createFlags.set("SDL_WINDOW_OPENGL", createFlagOpenGl);
	createFlags.set("SDL_WINDOW_SHOWN", createFlagShown);
	createFlags.set("SDL_WINDOW_HIDDEN", createFlagHidden);
	createFlags.set("SDL_WINDOW_BORDERLESS", createFlagBorderless);
	createFlags.set("SDL_WINDOW_RESIZABLE", createFlagResizable);
	createFlags.set("SDL_WINDOW_MINIMIZED", createFlagMinimized);
	createFlags.set("SDL_WINDOW_MAXIMIZED", createFlagMaximized);
	createFlags.set("SDL_WINDOW_MOUSE_GRABBED", createFlagMouseGrabbed);
	createFlags.set("SDL_WINDOW_INPUT_FOCUS", createFlagInputFocus);
	createFlags.set("SDL_WINDOW_MOUSE_FOCUS", createFlagMouseFocus);
	createFlags.set("SDL_WINDOW_FULLSCREEN_DESKTOP", createFlagFullscreenDesktop);
	createFlags.set("SDL_WINDOW_FOREIGN", createFlagForeign);
	createFlags.set("SDL_WINDOW_ALLOW_HIGH_DPI", createFlagAllowHighDpi);
	createFlags.set("SDL_WINDOW_MOUSE_CAPTURE", createFlagMouseCapture);
	createFlags.set("SDL_WINDOW_ALWAYS_ON_TOP", createFlagAlwaysOnTop);
	createFlags.set("SDL_WINDOW_SKIP_TASKBAR", createFlagSkipTaskbar);
	createFlags.set("SDL_WINDOW_UTILITY", createFlagUtility);
	createFlags.set("SDL_WINDOW_TOOLTIP", createFlagTooltip);
	createFlags.set("SDL_WINDOW_POPUP_MENU", createFlagPopupMenu);
	createFlags.set("SDL_WINDOW_KEYBOARD_GRABBED", createFlagKeyboardGrabbed);
	createFlags.set("SDL_WINDOW_VULKAN", createFlagVulkan);
	createFlags.set("SDL_WINDOW_METAL", createFlagMetal);
	json.set("init_flags", createFlags);

	json.save();
}

Uint32 Window::ConfigData::getInitFlags() const {
	Uint32 flag = 0U;
	flag |= initFlagTimer ? SDL_INIT_TIMER : 0U;
	flag |= initFlagAudio ? SDL_INIT_AUDIO : 0U;
	flag |= initFlagVideo ? SDL_INIT_VIDEO : 0U;
	flag |= initFlagJoystick ? SDL_INIT_JOYSTICK : 0U;
	flag |= initFlagHaptic ? SDL_INIT_HAPTIC : 0U;
	flag |= initFlagGameController ? SDL_INIT_GAMECONTROLLER : 0U;
	flag |= initFlagEvents ? SDL_INIT_EVENTS : 0U;
	flag |= initFlagSensor ? SDL_INIT_SENSOR : 0U;
	return flag;
}

Uint32 Window::ConfigData::getCreateFlags() const {
	Uint32 flag = 0U;
	flag |= createFlagFullscreen ? SDL_WINDOW_FULLSCREEN : 0U;
	flag |= createFlagOpenGl ? SDL_WINDOW_OPENGL : 0U;
	flag |= createFlagShown ? SDL_WINDOW_SHOWN : 0U;
	flag |= createFlagHidden ? SDL_WINDOW_HIDDEN : 0U;
	flag |= createFlagBorderless ? SDL_WINDOW_BORDERLESS : 0U;
	flag |= createFlagResizable ? SDL_WINDOW_RESIZABLE : 0U;
	flag |= createFlagMinimized ? SDL_WINDOW_MINIMIZED : 0U;
	flag |= createFlagMaximized ? SDL_WINDOW_MAXIMIZED : 0U;
	flag |= createFlagMouseGrabbed ? SDL_WINDOW_MOUSE_GRABBED : 0U;
	flag |= createFlagInputFocus ? SDL_WINDOW_INPUT_FOCUS : 0U;
	flag |= createFlagMouseFocus ? SDL_WINDOW_MOUSE_FOCUS : 0U;
	flag |= createFlagFullscreenDesktop ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0U;
	flag |= createFlagForeign ? SDL_WINDOW_FOREIGN : 0U;
	flag |= createFlagAllowHighDpi ? SDL_WINDOW_ALLOW_HIGHDPI : 0U;
	flag |= createFlagMouseCapture ? SDL_WINDOW_MOUSE_CAPTURE : 0U;
	flag |= createFlagAlwaysOnTop ? SDL_WINDOW_ALWAYS_ON_TOP : 0U;
	flag |= createFlagSkipTaskbar ? SDL_WINDOW_SKIP_TASKBAR : 0U;
	flag |= createFlagUtility ? SDL_WINDOW_UTILITY : 0U;
	flag |= createFlagTooltip ? SDL_WINDOW_TOOLTIP : 0U;
	flag |= createFlagPopupMenu ? SDL_WINDOW_POPUP_MENU : 0U;
	flag |= createFlagKeyboardGrabbed ? SDL_WINDOW_KEYBOARD_GRABBED : 0U;
	flag |= createFlagVulkan ? SDL_WINDOW_VULKAN : 0U;
	flag |= createFlagMetal ? SDL_WINDOW_METAL : 0U;
	return flag;
}

void Window::WindowDestroyer::operator()(SDL_Window* window) const {
	SDL_DestroyWindow(window);
	SDL_Quit();
}
