#pragma once

#include "Base/Window.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Workbench
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProperties& properties);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_WindowData.Width; }
		inline unsigned int GetHeight() const override { return m_WindowData.Height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_WindowData.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
	private:
		virtual void Init(const WindowProperties& properties);
		virtual void Shutdown();
	private:
		struct WindowData
		{
			std::string Title;
			unsigned int Width;
			unsigned int Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};
	private:
		GLFWwindow* m_Window;
		WindowData m_WindowData;
	};
}

