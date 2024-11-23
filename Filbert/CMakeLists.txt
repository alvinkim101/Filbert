add_library(Filbert SHARED
	src/Filbert.h
	src/Filbert/Core.h
	src/Filbert/EntryPoint.h
	src/Filbert/Application.cpp
	src/Filbert/Application.h
	src/Filbert/Log.cpp
	src/Filbert/Log.h
	src/Filbert/Events/ApplicationEvent.h
	src/Filbert/Events/Event.h
	src/Filbert/Events/KeyEvent.h
	src/Filbert/Events/MouseEvent.h
)

target_include_directories(Filbert PUBLIC src)
target_include_directories(Filbert PUBLIC vendor/spdlog/include)

# TODO: Figure out how to check Visual Studio's platform
target_compile_definitions(Filbert PUBLIC FB_PLATFORM_WINDOWS)
target_compile_definitions(Filbert PRIVATE FB_BUILD_DLL)

add_custom_command(TARGET Filbert POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	$<TARGET_FILE:Filbert> ${CMAKE_BINARY_DIR}/Sandbox/$<CONFIG>/$<TARGET_FILE_NAME:Filbert>
)
