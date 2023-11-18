#include <SDL.h>
#include <nlohmann/json.hpp>

#include <fstream>

int main() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    SDL_Log("SDL could not initialize! SDL Error: %s", SDL_GetError());
    return -1;
  }

  std::string configPath = "../config/window.json";
  std::ifstream configFile(configPath);
  if (!configFile.is_open()) {
    SDL_Log("ERROR: File %s not found", configPath.c_str());
    return 0;
  }
  nlohmann::json configJson = nlohmann::json::parse(configFile);

  std::string title = configJson.at("title");
  int width = configJson.at("width");
  int height = configJson.at("height");

  // Create a window
  SDL_Window* window = SDL_CreateWindow(title.c_str(), width, height, 0);

  if (window == nullptr) {
    SDL_Log("Window could not be created! SDL Error: %s", SDL_GetError());
    return -1;
  }

  // Create a renderer for the window
  SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr, SDL_RENDERER_ACCELERATED);

  if (renderer == nullptr) {
    SDL_Log("Renderer could not be created! SDL Error: %s", SDL_GetError());
    return -1;
  }

  // Render the scene
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_FRect rect { 100, 200, 400, 200 };
  SDL_RenderFillRect(renderer, &rect);

  SDL_RenderPresent(renderer);

  // Main loop
  bool quit = false;
  SDL_Event e;

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_EVENT_QUIT) quit = true;
    }
    SDL_GL_SwapWindow(window);
  }

  // Cleanup and exit
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}