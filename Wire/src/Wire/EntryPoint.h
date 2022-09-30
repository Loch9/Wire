#pragma once

#ifdef WR_PLATFORM_WINDOWS

extern Wire::Application* Wire::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Wire::CreateApplication();
	app->Run();
	delete app;
}

#endif
