#pragma once

#include "Core.h"

namespace Wire {

	class WIRE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();

}


