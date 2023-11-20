# SDL
add_subdirectory(SDL)
set(SDL_TEST OFF)

# json
add_subdirectory(json)

# imgui
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
add_library(ImGui STATIC)

target_sources( ImGui
                PRIVATE
                    ${IMGUI_DIR}/imgui_demo.cpp
                    ${IMGUI_DIR}/imgui_draw.cpp
                    ${IMGUI_DIR}/imgui_tables.cpp
                    ${IMGUI_DIR}/imgui_widgets.cpp
                    ${IMGUI_DIR}/imgui.cpp

                PRIVATE
                    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
                    ${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp
                )

target_include_directories( ImGui
                            PUBLIC ${IMGUI_DIR}
                            PUBLIC ${IMGUI_DIR}/backends
                            PUBLIC ${SDL3_DIR}/include
                            )




# submodules
add_library(submodules INTERFACE)
target_link_libraries(submodules INTERFACE
        SDL3::SDL3
        nlohmann_json::nlohmann_json
        ImGui
)
