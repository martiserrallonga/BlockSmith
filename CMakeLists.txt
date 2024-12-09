cmake_minimum_required (VERSION 3.13)

project ("BlockSmith")
add_executable (${PROJECT_NAME})

# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG=$<IF:$<CONFIG:Debug>,1,0>)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

find_package (imgui CONFIG REQUIRED)
target_link_libraries (${PROJECT_NAME} PRIVATE imgui::imgui)

find_package (nlohmann_json CONFIG REQUIRED)
target_link_libraries (${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

add_custom_target (copy_config COMMAND ${CMAKE_COMMAND}
    -E copy_directory "${PROJECT_SOURCE_DIR}/config" "${CMAKE_BINARY_DIR}/config"
)

# file(WRITE "${CMAKE_BINARY_DIR}/.clang-tidy" "Checks: '-*'")

add_dependencies (${PROJECT_NAME} copy_config)

add_subdirectory (src)