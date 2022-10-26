#include "wrpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Wire {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		WR_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		WR_CORE_ASSERT(status, "Failed to initialize Glad!");

		WR_CORE_INFO("OpenGL Info:");
		WR_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		WR_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		WR_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}
