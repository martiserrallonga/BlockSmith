#pragma once
#include "GameEngine.h"

namespace Engine
{
	struct EngineGetter
	{
		inline static GameEngine engine;
	};

	GameEngine& Get();
}
