#include <SDL.h>
#include <fstream>
#include <nlohmann/json.hpp>

class MyShortClass {
public:
  // MyShortClass(int x, int y) : x(x), y(y) {
  // 	// Some code here
  // }

  // private:
  int x;
  int y;
};

class MyClass {
public:
  // MyClass(
  // 		float number_name_number_1, float number_name_number_2, float number_name_number_3, float number_name_number_11, float number_name_number_12,
  // 		float number_name_number_13, float number_name_number_21, float number_name_number_22, float number_name_number_23, float number_name_number_31,
  // 		float number_name_number_32, float number_name_number_33
  // )
  // 		: number_name_number_1(number_name_number_1)
  // 		, number_name_number_2(number_name_number_2)
  // 		, number_name_number_3(number_name_number_3)
  // 		, number_name_number_11(number_name_number_11)
  // 		, number_name_number_12(number_name_number_12)
  // 		, number_name_number_13(number_name_number_13)
  // 		, number_name_number_21(number_name_number_21)
  // 		, number_name_number_22(number_name_number_22)
  // 		, number_name_number_23(number_name_number_23)
  // 		, number_name_number_31(number_name_number_31)
  // 		, number_name_number_32(number_name_number_32)
  // 		, number_name_number_33(number_name_number_33) {
  // 	int n = static_cast<int>(number_name_number_1);

  // 	std::string name;
  // 	switch (n) {
  // 	case 1: name = "Pedro";
  // 	case 2:
  // 	case 3: name = "Juan"; break;
  // 	default: name = "Undefined"; break;
  // 	}
  // 	SDL_Log("Hello %s", name.c_str());
  // }

  // private:
  float number_name_number_1;
  float number_name_number_2;
  float number_name_number_3;
  float number_name_number_11;
  float number_name_number_12;
  float number_name_number_13;
  float number_name_number_21;
  float number_name_number_22;
  float number_name_number_23;
  float number_name_number_31;
  float number_name_number_32;
  float number_name_number_33;
};


int main() {
  // float number_name_number_1, number_name_number_2, number_name_number_3, number_name_number_11, number_name_number_12, number_name_number_13,
  // 		number_name_number_21, number_name_number_22, number_name_number_23, number_name_number_31, number_name_number_32, number_name_number_33;

  // MyClass myExample(
  // 		number_name_number_1, number_name_number_2, number_name_number_3, number_name_number_11, number_name_number_12, number_name_number_13,
  // 		number_name_number_21, number_name_number_22, number_name_number_23, number_name_number_31, number_name_number_32, number_name_number_33
  // );

  MyClass other {
    .number_name_number_1 = 34.f,
    .number_name_number_2 = 34.f,
    .number_name_number_3 = 34.f,
    .number_name_number_11 = 34.f,
    .number_name_number_12 = 34.f,
    .number_name_number_13 = 34.f,
    .number_name_number_21 = 34.f,
    .number_name_number_22 = 34.f,
    .number_name_number_23 = 34.f,
    .number_name_number_31 = 34.f,
    .number_name_number_32 = 34.f,
    .number_name_number_33 = 34.f,
  };

  MyShortClass shortClass {
    .x = 1,
    .y = 2,
  };

  MyShortClass shortClassSecond { 11, 22 };

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