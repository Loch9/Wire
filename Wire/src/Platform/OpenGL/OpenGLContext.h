#pragma once

#include "Wire/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Wire {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* winowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}