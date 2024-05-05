#pragma once

class Renderer;
class Window;

class Context
{
public:
	static void init(const Window& window, const Renderer& renderer);
};