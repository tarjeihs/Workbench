#include "wbpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Workbench
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle) 
	{
		WB_ENGINE_ASSERT(windowHandle, "Failed to locate GLFW window handle pointer.");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		WB_ENGINE_ASSERT(success, "Failed to initialize GLAD library.");

		WB_ENGINE_INFO("OpenGL Render Info:");
		WB_ENGINE_INFO("\tVendor: {0}", glGetString(GL_VENDOR));
		WB_ENGINE_INFO("\tRenderer: {0}", glGetString(GL_RENDERER));
		WB_ENGINE_INFO("\tVersion: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}