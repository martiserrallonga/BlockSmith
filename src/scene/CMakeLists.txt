target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

set (SOURCES PRIVATE
	Entity.cpp
	Entity.h
	Scene.cpp
	Scene.h
)

target_sources (${PROJECT_NAME} PRIVATE ${SOURCES})
