#include <Wire.h>

class Sandbox : public Wire::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
  
};

Wire::Application* Wire::CreateApplication()
{
	return new Sandbox();
}