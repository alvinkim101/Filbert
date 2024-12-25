set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/imgui)

add_library(Filbert STATIC
	src/Filbert.h
	src/pch.h
	src/Filbert/Core/Core.h
	src/Filbert/Core/EntryPoint.h
	src/Filbert/Core/Application.cpp
	src/Filbert/Core/Application.h
	src/Filbert/Core/Layer.h
	src/Filbert/Core/LayerStack.cpp
	src/Filbert/Core/LayerStack.h
	src/Filbert/Core/Log.cpp
	src/Filbert/Core/Log.h
	src/Filbert/Core/Window.cpp
	src/Filbert/Core/Window.h
	src/Filbert/Events/ApplicationEvent.h
	src/Filbert/Events/Event.h
	src/Filbert/Events/KeyEvent.h
	src/Filbert/Events/MouseEvent.h
	src/Filbert/ImGui/ImGuiLayer.cpp
	src/Filbert/ImGui/ImGuiLayer.h
	src/Filbert/Input/Input.h
	src/Filbert/Input/KeyCodes.h
	src/Filbert/Input/MouseButtonCodes.h
	src/Filbert/Renderer/Buffer.cpp
	src/Filbert/Renderer/Buffer.h
	src/Filbert/Renderer/Camera.cpp
	src/Filbert/Renderer/Camera.h
	src/Filbert/Renderer/CameraController.cpp
	src/Filbert/Renderer/CameraController.h
	src/Filbert/Renderer/RenderCommand.cpp
	src/Filbert/Renderer/RenderCommand.h
	src/Filbert/Renderer/Renderer.cpp
	src/Filbert/Renderer/Renderer.h
	src/Filbert/Renderer/RendererAPI.cpp
	src/Filbert/Renderer/RendererAPI.h
	src/Filbert/Renderer/Shader.cpp
	src/Filbert/Renderer/Shader.h
	src/Filbert/Renderer/Texture.cpp
	src/Filbert/Renderer/Texture.h
	src/Filbert/Renderer/VertexArray.cpp
	src/Filbert/Renderer/VertexArray.h
	src/Platform/OpenGL/OpenGLBuffer.cpp
	src/Platform/OpenGL/OpenGLBuffer.h
	src/Platform/OpenGL/OpenGLRendererAPI.cpp
	src/Platform/OpenGL/OpenGLRendererAPI.h
	src/Platform/OpenGL/OpenGLShader.cpp
	src/Platform/OpenGL/OpenGLShader.h
	src/Platform/OpenGL/OpenGLTexture.cpp
	src/Platform/OpenGL/OpenGLTexture.h
	src/Platform/OpenGL/OpenGLVertexArray.cpp
	src/Platform/OpenGL/OpenGLVertexArray.h
	src/Platform/OpenGL/OpenGLInput.cpp
	src/Platform/OpenGL/OpenGLInput.h
	src/Platform/OpenGL/OpenGLWindow.cpp
	src/Platform/OpenGL/OpenGLWindow.h
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
target_include_directories(Filbert PUBLIC vendor/stb)

target_compile_definitions(Filbert PUBLIC $<$<PLATFORM_ID:Windows>:FB_PLATFORM_WINDOWS>)
target_compile_definitions(Filbert PUBLIC $<$<CONFIG:Debug>:FB_ASSERTS_ENABLED>)

target_precompile_headers(Filbert PUBLIC src/pch.h)
