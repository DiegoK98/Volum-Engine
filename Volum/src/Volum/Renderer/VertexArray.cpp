#include "vlmpch.h"

#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Volum
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				VLM_CORE_ASSERT(false, "RendererAPI::None is not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLVertexArray>();
		}

		VLM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}