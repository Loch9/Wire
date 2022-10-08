#pragma once

#ifdef WR_PLATFORM_WINDOWS
	#ifdef WR_BUILD_DLL
		#define WIRE_API __declspec(dllexport)
	#else
		#define WIRE_API __declspec(dllimport)
	#endif
#else
	#error Wire only supports Windows!
#endif

#ifdef WR_DEBUG
	#define WR_ENABLE_ASSERTS
#endif

#ifdef WR_ENABLE_ASSERTS
	#define WR_ASSERT(x, ...) { if(!(x)) { WR_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define WR_CORE_ASSERT(x, ...) { if(!(x)) { WR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define WR_ASSERT(x, ...)
	#define WR_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)