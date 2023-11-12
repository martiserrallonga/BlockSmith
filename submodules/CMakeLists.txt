set(SDL_TEST OFF)
add_subdirectory(SDL)

add_library(submodules INTERFACE)
target_link_libraries(submodules INTERFACE SDL3::SDL3)