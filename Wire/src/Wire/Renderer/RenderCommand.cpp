#include "wrpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Wire {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}