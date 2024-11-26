set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)

add_library(Filbert SHARED
	src/Filbert.h
	src/pch.h
	src/Filbert/Core.h
	src/Filbert/EntryPoint.h
	src/Filbert/Application.cpp
	src/Filbert/Application.h
	src/Filbert/Layer.h
	src/Filbert/LayerStack.cpp
	src/Filbert/LayerStack.h
	src/Filbert/Log.cpp
	src/Filbert/Log.h
	src/Filbert/Window.h
	src/Filbert/Events/ApplicationEvent.h
	src/Filbert/Events/Event.h
	src/Filbert/Events/KeyEvent.h
	src/Filbert/Events/MouseEvent.h
	src/Platform/Windows/WindowsWindow.cpp
	src/Platform/Windows/WindowsWindow.h
)

target_link_libraries(Filbert glfw)
target_link_libraries(Filbert glad)

target_include_directories(Filbert PUBLIC src)
target_include_directories(Filbert PUBLIC vendor/spdlog/include)
target_include_directories(Filbert PUBLIC vendor/glfw/include)
target_include_directories(Filbert PUBLIC vendor/glad/include)

target_compile_definitions(Filbert PUBLIC $<$<PLATFORM_ID:Windows>:FB_PLATFORM_WINDOWS>)
target_compile_definitions(Filbert PUBLIC $<$<CONFIG:Debug>:FB_ASSERTS_ENABLED>)
target_compile_definitions(Filbert PRIVATE FB_BUILD_DLL)

target_precompile_headers(Filbert PUBLIC src/pch.h)

add_custom_command(TARGET Filbert POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	$<TARGET_FILE:Filbert> ${CMAKE_BINARY_DIR}/Sandbox/$<CONFIG>/$<TARGET_FILE_NAME:Filbert>
)
