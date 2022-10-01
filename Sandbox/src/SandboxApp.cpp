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
<<<<<<< HEAD
=======

>>>>>>> temp
};

Wire::Application* Wire::CreateApplication()
{
	return new Sandbox();
}