add_executable(Editor
	src/Editor.cpp
	src/EditorLayer.cpp
	src/EditorLayer.h
)

target_link_libraries(Editor Filbert)

add_custom_command(TARGET Editor POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
	${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
