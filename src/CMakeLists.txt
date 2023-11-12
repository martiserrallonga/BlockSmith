add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE submodules)

# Copy config files command
add_custom_target(copy_config COMMAND ${CMAKE_COMMAND}
        -E copy_directory "${PROJECT_SOURCE_DIR}/config" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/config")
add_dependencies(${PROJECT_NAME} copy_config)