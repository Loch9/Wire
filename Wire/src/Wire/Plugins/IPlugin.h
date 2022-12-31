#pragma once

#include "Wire/Events/Event.h"
#include "Wire/Core/Timestep.h"

namespace Wire {

	class IPlugin
	{
	public:
		virtual void Setup() = 0;
		virtual void OnUpdate(Timestep ts) = 0;
		virtual void OnEvent(Event& e) = 0;
	};

}
