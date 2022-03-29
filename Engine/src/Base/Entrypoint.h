#pragma once

#ifdef WB_PLATFORM_WINDOWS

extern Workbench::Application* Workbench::CreateApplication();

int main(int argc, char** argv)
{
	Workbench::Log::Init();
	
	WB_ENGINE_TRACE("Hello World!");

	auto application = Workbench::CreateApplication();
	application->Run();
	delete application;
}

#endif