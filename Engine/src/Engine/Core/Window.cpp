#include "wbpch.h"
#include "Engine/Core/Window.h"

#ifdef WB_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Workbench
{
	Window* Window::Create(const WindowProperties& properties)
	{
		return new WindowsWindow(properties);
	}
}
