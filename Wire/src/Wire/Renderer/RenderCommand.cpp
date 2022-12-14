#include "wrpch.h"
#include "Wire/Renderer/RenderCommand.h"

namespace Wire {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}