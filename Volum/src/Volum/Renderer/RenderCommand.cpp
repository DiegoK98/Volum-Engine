#include "vlmpch.h"

#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Volum
{
	Scope<RendererAPI> RenderCommand::s_rendererAPI = CreateScope<OpenGLRendererAPI>();
}