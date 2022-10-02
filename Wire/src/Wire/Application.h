#pragma once

#include "Core.h"
#include "Events/Event.h"

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
