target_include_directories (${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

set (SOURCES PRIVATE
	DropdownValue.cpp
	DropdownValue.h
	Settings.cpp
	Settings.h
)

target_sources (${PROJECT_NAME} PRIVATE ${SOURCES})
