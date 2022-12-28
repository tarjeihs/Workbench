#include "wbpch.h"
#include "Platform/Windows/WindowsWindow.h"

namespace Workbench
{
	static bool s_GLFWInitialized = false;
	static bool s_GLADInitialized = false;

	WindowsWindow::WindowsWindow(const WindowProperties& properties)
	{
		Init(properties);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProperties& properties)
	{
		m_WindowData.Title = properties.Title;
		m_WindowData.Width = properties.Width;
		m_WindowData.Height = properties.Height;

		WB_ENGINE_INFO("Creating window {0} ({1}, {2})", properties.Title, properties.Width, properties.Height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			WB_ENGINE_ASSERT(success, "Failed to initialize GLFW library.");

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)properties.Width, (int)properties.Height, m_WindowData.Title.c_str(), nullptr, nullptr);
		
		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_WindowData);

		// GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowResizeEvent event(width, height);
			data.Width = width;
			data.Height = height;
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int keyCode, int scanCode, int action, int modes)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS: { KeyPressedEvent event(keyCode, 0); data.EventCallback(event); break; }
				case GLFW_REPEAT: { KeyPressedEvent event(keyCode, 1); data.EventCallback(event); break; }
				case GLFW_RELEASE: { KeyReleasedEvent event(keyCode); data.EventCallback(event); break; }
			}
		});		
		
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keyCode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypeEvent event(keyCode);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double mouseX, double mouseY)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMoveEvent event((float)mouseX, (float)mouseY);
			data.EventCallback(event);
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrollEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int keyCode, int action, int mods) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS: { MouseButtonPressedEvent event(keyCode); data.EventCallback(event); break; }
				case GLFW_RELEASE: { MouseButtonReleasedEvent event(keyCode); data.EventCallback(event); break; }
			}
		});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		glfwSwapInterval(enabled);

		m_WindowData.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_WindowData.VSync;
	}
}