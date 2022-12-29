#include "wrpch.h"
#include "Window.h"

#ifdef WR_PLATFORM_WINDOWS
 #include "Platform/Windows/WindowsWindow.h"
#endif

namespace Wire {

	Scope<Window> Window::Create(const WindowProps& props)
	{
#ifdef WR_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#else
		WR_CORE_ASSERT(false, "Unsupported platform!");
		return nullptr;
#endif
	}

}