#pragma once

#ifdef FB_PLATFORM_WINDOWS
	#ifdef FB_BUILD_DLL
		#define FILBERT_API __declspec(dllexport)
	#else
		#define FILBERT_API __declspec(dllimport)
	#endif
#else
	#error "Filbert only supports Windows"
#endif

#ifdef FB_ASSERTS_ENABLED
	#define FB_CORE_ASSERT(x, ...) if (!x) { FB_CORE_ERROR("Assertion failed: {}", __VA_ARGS__); __debugbreak(); }
	#define FB_ASSERT(x, ...) if (!x) { FB_ERROR("Assertion failed: {}", __VA_ARGS__); __debugbreak(); }
#else
	#define FB_CORE_ASSERT(x, ...)
	#define FB_ASSERT(x, ...)
#endif
