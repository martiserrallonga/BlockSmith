#include "EngineGetter.h"

namespace Engine
{
  GameEngine& Get() {
    return EngineGetter::engine;
  }
}
