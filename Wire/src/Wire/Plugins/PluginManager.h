#pragma once

#include <vector>

#include "IPlugin.h"

#include "Wire/Core/Timestep.h"

namespace Wire {

	class PluginManager
	{
	public:
		PluginManager();

		void Add(Ref<IPlugin> plugin) { m_Plugins.push_back(plugin); }

		void Setup();
		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);
	private:
		std::vector<Ref<IPlugin>> m_Plugins;
	};

}
