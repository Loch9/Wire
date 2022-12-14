#include "wrpch.h"
#include "Wire/Renderer/VertexArray.h"

#include "Wire/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Wire {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    WR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexArray>();
		}

		WR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}