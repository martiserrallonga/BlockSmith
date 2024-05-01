target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

set (SOURCES PRIVATE
	Logger.cpp
	Logger.h
	LoggerGetter.cpp
	LoggerGetter.h
)

target_sources (${PROJECT_NAME} PRIVATE ${SOURCES})
