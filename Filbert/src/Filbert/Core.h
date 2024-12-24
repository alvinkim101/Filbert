#pragma once

#ifdef FB_ASSERTS_ENABLED
	#define FB_CORE_ASSERT(x, ...) if (!(x)) { FB_CORE_ERROR("Assertion failed: {}", __VA_ARGS__); __debugbreak(); }
	#define FB_ASSERT(x, ...) if (!(x)) { FB_ERROR("Assertion failed: {}", __VA_ARGS__); __debugbreak(); }
#else
	#define FB_CORE_ASSERT(x, ...)
	#define FB_ASSERT(x, ...)
#endif

#define FB_BIND_EVENT_FN(f) std::bind(&f, this, std::placeholders::_1)
