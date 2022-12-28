#pragma once

#include "Engine/Core/Base.h"

#include "Engine/Event/Event.h"
#include "Engine/Event/ApplicationEvent.h"
#include "Engine/Event/KeyEvent.h"
#include "Engine/Event/MouseEvent.h"

#include <sstream>

namespace Workbench
{
	struct WindowProperties
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProperties(const std::string& title = "Workbench",
					unsigned int width = 1280,
					unsigned int height = 720)
			: Title(title), Width(width), Height(height) {}
	};

	// Interface and Create function to be defined per platform.
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProperties& properties = WindowProperties());
	};
}