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
