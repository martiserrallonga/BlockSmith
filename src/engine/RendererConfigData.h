#pragma once

#include "LoggerGetter.h"
#include "JsonWrapper.h"

#include <string>


struct RendererConfigData
{
	std::string filePath;

	bool flagSoftware = false;
	bool flagAccelerated = false;
	bool flagPresentVSync = false;
	bool flagTargetTexture = false;

	RendererConfigData() = default;
	RendererConfigData(std::string filePath)
		: filePath(filePath)
	{}

	bool load() {
		auto config = Json::Parse(filePath);
		Json flags = config.get("flags");
		flagSoftware = flags.get("SDL_RENDERER_SOFTWARE", false);
		flagAccelerated = flags.get("SDL_RENDERER_ACCELERATED", true);
		flagPresentVSync = flags.get("SDL_RENDERER_PRESENT_VSYNC", true);
		flagTargetTexture = flags.get("SDL_RENDERER_TARGET_TEXTURE", false);

		return true;
	}

	void save() {

	}
};