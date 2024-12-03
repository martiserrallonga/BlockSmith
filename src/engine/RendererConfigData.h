#pragma once

#include <string>

struct RendererConfigData
{
	RendererConfigData(std::string filename)
		: filename(filename)
	{}

	std::string filename;

	bool flagSoftware = false;
	bool flagAccelerated = false;
	bool flagPresentVSync = false;
	bool flagTargetTexture = false;

	void read() {

	}

	void save() {

	}
};