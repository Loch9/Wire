#pragma once

#ifdef WR_PLATFORM_WINDOWS

extern Wire::Application* Wire::CreateApplication();

int main(int argc, char** argv)
{
	Wire::Log::Init();
	WR_CORE_WARN("Initialized Log!");
	int a = 5;
	WR_INFO("Hello! Var={0}", a);

	auto app = Wire::CreateApplication();
	app->Run();
	delete app;
}

#endif