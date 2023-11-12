# SDL
add_subdirectory(SDL)
set(SDL_TEST OFF)

# json
add_subdirectory(json)

# submodules
add_library(submodules INTERFACE)
target_link_libraries(submodules INTERFACE
        SDL3::SDL3
        nlohmann_json::nlohmann_json
)
