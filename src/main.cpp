#define SDL_MAIN_HANDLED
#include "EngineGetter.h"

int main() {
	Engine::GameEngine& engine = Engine::Get();
	if (!engine.initialize()) return -1;

	while (engine.handleEvents()) {
		engine.update();
		engine.render();
	}

	return 0;
}
