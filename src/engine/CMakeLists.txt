target_include_directories (${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

set (SOURCES PRIVATE
	Context.cpp
	Context.h
	EngineGetter.cpp
	EngineGetter.h
	GameEngine.cpp
	GameEngine.h
	Renderer.cpp
	Renderer.h
	Window.cpp
	Window.h
)

target_sources (${PROJECT_NAME} PRIVATE ${SOURCES})
