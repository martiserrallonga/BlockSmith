#pragma once

#include "DropdownValue.h"

class Renderer;
class Window;

class Menu
{
public:
	Menu();

	void render();

private:
	int _counter = 0;
	float _value = 0.f;

	bool _showDemoWindow = false;
	bool _showExtraWindow = false;
	DropdownValue _logLevel;
};
