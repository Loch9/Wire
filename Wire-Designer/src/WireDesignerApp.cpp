#include <Wire.h>
#include <Wire/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Wire {

	class WireDesigner : public Application
	{
	public:
		WireDesigner()
			: Application("Wire Designer")
		{
			PushLayer(new EditorLayer());
		}

		~WireDesigner()
		{
		}
	};

	Application* CreateApplication()
	{
		return new WireDesigner();
	}

}
