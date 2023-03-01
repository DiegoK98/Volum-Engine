#include "vlmpch.h"

#include "RenderCommand.h"

namespace Volum
{
	Scope<RendererAPI> RenderCommand::s_rendererAPI = RendererAPI::Create();
}