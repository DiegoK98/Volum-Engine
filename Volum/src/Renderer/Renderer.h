#pragma once

#include "RenderCommand.h"

namespace Volum
{
	class Renderer
	{
	public:
		static void BeginScene();
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
		static void EndScene();

		static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); };
	};
}