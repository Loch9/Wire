#pragma once

#ifdef WR_PLATFORM_WINDOWS

extern Wire::Application* Wire::CreateApplication();

int main(int argc, char** argv)
{
<<<<<<< HEAD
=======
	Wire::Log::Init();
	WR_CORE_WARN("Initialized Log!");
	int a = 5;
	WR_INFO("Hello! Var={0}", a);

>>>>>>> temp
	auto app = Wire::CreateApplication();
	app->Run();
	delete app;
}

<<<<<<< HEAD
#endif
=======
#endif
>>>>>>> temp
