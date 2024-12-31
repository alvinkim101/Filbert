add_executable(Sandbox
	src/Sandbox2D.cpp
	src/Sandbox2D.h
	src/SandboxApp.cpp
)

target_link_libraries(Sandbox Filbert)

add_custom_command(TARGET Sandbox POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
	${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
