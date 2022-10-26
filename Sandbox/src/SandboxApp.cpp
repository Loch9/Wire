#include <Wire.h>

#include "imgui/imgui.h"

class ExampleLayer : public Wire::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (Wire::Input::IsKeyPressed(WR_KEY_TAB))
			WR_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(Wire::Event& event) override
	{
		if (event.GetEventType() == Wire::EventType::KeyPressed)
		{
			Wire::KeyPressedEvent& e = (Wire::KeyPressedEvent&)event;
			if (e.GetKeyCode() == WR_KEY_TAB)
				WR_TRACE("Tab key is pressed (event)!");
			WR_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

};

class Sandbox : public Wire::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

Wire::Application* Wire::CreateApplication()
{
	return new Sandbox();
}