#include "Application.h"

#include "Wire/Events/ApplicationEvent.h"
#include "Wire/Log.h"

namespace Wire {

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1200, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			WR_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			WR_TRACE(e);
		}

		while (true);
	}

}