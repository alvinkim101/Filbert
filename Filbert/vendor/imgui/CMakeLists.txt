add_library(imgui STATIC
	imgui/imconfig.h
	imgui/imgui.cpp
	imgui/imgui.h
	imgui/imgui_demo.cpp
	imgui/imgui_draw.cpp
	imgui/imgui_internal.h
	imgui/imgui_tables.cpp
	imgui/imgui_widgets.cpp
	imgui/imstb_rectpack.h
	imgui/imstb_textedit.h
	imgui/imstb_truetype.h
	imgui/backends/imgui_impl_glfw.cpp
	imgui/backends/imgui_impl_glfw.h
	imgui/backends/imgui_impl_opengl3.cpp
	imgui/backends/imgui_impl_opengl3.h
	imgui/backends/imgui_impl_opengl3_loader.h
	imgui/misc/cpp/imgui_stdlib.cpp
	imgui/misc/cpp/imgui_stdlib.h
	imgui/misc/debuggers/imgui.natstepfilter
	imgui/misc/debuggers/imgui.natvis
)

target_include_directories(imgui PRIVATE imgui imgui/backends imgui/misc/cpp)
target_include_directories(imgui PRIVATE ../glfw/include)
