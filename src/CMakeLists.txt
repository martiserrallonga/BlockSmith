target_include_directories (${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory (logger)
add_subdirectory (time)
add_subdirectory (ui)

set (SOURCES PRIVATE
	main.cpp
)

target_sources (${PROJECT_NAME} PRIVATE ${SOURCES})
