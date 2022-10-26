#pragma once

#include "Wire/Layer.h"

#include "Wire/Events/ApplicationEvent.h"
#include "Wire/Events/KeyEvent.h"
#include "Wire/Events/MouseEvent.h"

namespace Wire {

	class WIRE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}