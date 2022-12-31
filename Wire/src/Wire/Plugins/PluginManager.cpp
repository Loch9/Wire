#include "wrpch.h"
#include "PluginManager.h"

namespace Wire {

	PluginManager::PluginManager()
	{
	}

	void PluginManager::Setup()
	{
		for (Ref<IPlugin> plugin : m_Plugins)
			plugin->Setup();
	}

	void PluginManager::OnUpdate(Timestep ts)
	{
		for (Ref<IPlugin> plugin : m_Plugins)
			plugin->OnUpdate(ts);
	}

	void PluginManager::OnEvent(Event& e)
	{
		for (Ref<IPlugin> plugin : m_Plugins)
			plugin->OnEvent(e);
	}

}
