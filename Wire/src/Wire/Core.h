#pragma once

#ifdef WR_PLATFORM_WINDOWS
	#ifdef WR_BUILD_DLL
		#define WIRE_API __declspec(dllexport)
	#else
<<<<<<< HEAD
		#define WIRE_API __declspec(dllexport)
=======
		#define WIRE_API __declspec(dllimport)
>>>>>>> temp
	#endif
#else
	#error Wire only supports Windows!
#endif