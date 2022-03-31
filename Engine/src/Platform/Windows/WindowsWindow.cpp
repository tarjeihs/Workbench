#include "wbpch.h"
#include "WindowsWindow.h"

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

	Window* Window::Create(const WindowProperties& properties)
	{
		return new WindowsWindow(properties);
	}

	void WindowsWindow::Init(const WindowProperties& properties)
	{
		m_WindowData.Title = properties.Title;
		m_WindowData.Width = properties.Width;
		m_WindowData.Height = properties.Height;

		WB_ENGINE_INFO("Creating OpenGL window {0} ({1}, {2})", properties.Title, properties.Width, properties.Height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			WB_ENGINE_ASSERT(success, "Failed to initialize GLFW library.");

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)properties.Width, (int)properties.Height, m_WindowData.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_WindowData);
		SetVSync(true);

		if (!s_GLADInitialized)
		{
			int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			WB_ENGINE_ASSERT(status, "Failed to initialize GLAD library.");

			s_GLADInitialized = true;
		}

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
		glfwSwapBuffers(m_Window);
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