set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/imgui)

add_library(Filbert STATIC
	src/Filbert.h
	src/pch.h
	src/Filbert/Core.h
	src/Filbert/EntryPoint.h
	src/Filbert/Application.cpp
	src/Filbert/Application.h
	src/Filbert/Input.h
	src/Filbert/KeyCodes.h
	src/Filbert/Layer.h
	src/Filbert/LayerStack.cpp
	src/Filbert/LayerStack.h
	src/Filbert/Log.cpp
	src/Filbert/Log.h
	src/Filbert/MouseButtonCodes.h
	src/Filbert/Window.h
	src/Filbert/Events/ApplicationEvent.h
	src/Filbert/Events/Event.h
	src/Filbert/Events/KeyEvent.h
	src/Filbert/Events/MouseEvent.h
	src/Filbert/ImGui/ImGuiLayer.cpp
	src/Filbert/ImGui/ImGuiLayer.h
	src/Filbert/Renderer/Buffer.cpp
	src/Filbert/Renderer/Buffer.h
	src/Filbert/Renderer/Camera.cpp
	src/Filbert/Renderer/Camera.h
	src/Filbert/Renderer/Context.cpp
	src/Filbert/Renderer/Context.h
	src/Filbert/Renderer/RenderCommand.cpp
	src/Filbert/Renderer/RenderCommand.h
	src/Filbert/Renderer/Renderer.cpp
	src/Filbert/Renderer/Renderer.h
	src/Filbert/Renderer/RendererAPI.cpp
	src/Filbert/Renderer/RendererAPI.h
	src/Filbert/Renderer/Shader.cpp
	src/Filbert/Renderer/Shader.h
	src/Filbert/Renderer/VertexArray.cpp
	src/Filbert/Renderer/VertexArray.h
	src/Platform/OpenGL/OpenGLBuffer.cpp
	src/Platform/OpenGL/OpenGLBuffer.h
	src/Platform/OpenGL/OpenGLContext.cpp
	src/Platform/OpenGL/OpenGLContext.h
	src/Platform/OpenGL/OpenGLRendererAPI.cpp
	src/Platform/OpenGL/OpenGLRendererAPI.h
	src/Platform/OpenGL/OpenGLShader.cpp
	src/Platform/OpenGL/OpenGLShader.h
	src/Platform/OpenGL/OpenGLVertexArray.cpp
	src/Platform/OpenGL/OpenGLVertexArray.h
	src/Platform/Windows/WindowsInput.cpp
	src/Platform/Windows/WindowsInput.h
	src/Platform/Windows/WindowsWindow.cpp
	src/Platform/Windows/WindowsWindow.h
)

target_link_libraries(Filbert glfw)
target_link_libraries(Filbert glad)
target_link_libraries(Filbert imgui)

target_include_directories(Filbert PUBLIC src)
target_include_directories(Filbert PUBLIC vendor/spdlog/include)
target_include_directories(Filbert PUBLIC vendor/glfw/include)
target_include_directories(Filbert PUBLIC vendor/glad/include)
target_include_directories(Filbert PUBLIC vendor/imgui/imgui vendor/imgui/imgui/backends vendor/imgui/imgui/misc/cpp)
target_include_directories(Filbert PUBLIC vendor/glm)

target_compile_definitions(Filbert PUBLIC $<$<PLATFORM_ID:Windows>:FB_PLATFORM_WINDOWS>)
target_compile_definitions(Filbert PUBLIC $<$<CONFIG:Debug>:FB_ASSERTS_ENABLED>)

target_precompile_headers(Filbert PUBLIC src/pch.h)
