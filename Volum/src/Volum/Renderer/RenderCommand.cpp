#include "vlmpch.h"

#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Volum
{
	RendererAPI* RenderCommand::s_rendererAPI = new OpenGLRendererAPI;
}