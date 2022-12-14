#include "wrpch.h"
#include "OpenGLContext.h"

#include <glfw/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Wire {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		WR_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		WR_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		WR_CORE_ASSERT(status, "Failed to initialize Glad!");

		WR_CORE_INFO("OpenGL Info:");
		WR_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		WR_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		WR_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

	#ifdef WR_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		WR_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Wire requires at least OpenGL version 4.5!");
	#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		WR_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}