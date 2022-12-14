#include "wrpch.h"
#include "Wire/Renderer/GraphicsContext.h"

#include "Wire/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Wire {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    WR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		WR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}