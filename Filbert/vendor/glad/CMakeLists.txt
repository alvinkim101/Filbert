add_library(glad STATIC
	include/glad/gl.h
	include/KHR/khrplatform.h
    src/gl.c
)

target_include_directories(glad PRIVATE include)
