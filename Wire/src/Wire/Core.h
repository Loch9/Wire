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

#define BIT(x) (1 << x)