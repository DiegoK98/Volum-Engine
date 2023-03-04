#pragma once

#include "Volum/Renderer/RendererAPI.h"

namespace Volum
{
	class RenderCommand
	{
	public:
		static void Init()
		{
			VLM_PROFILE_FUNCTION();

			s_rendererAPI->Init();
		}

		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_rendererAPI->SetViewport(x, y, width, height);
		}

		static void SetClearColor(const glm::vec4& color)
		{
			s_rendererAPI->SetClearColor(color);
		}

		static void Clear()
		{
			s_rendererAPI->Clear();
		}

		static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0)
		{
			s_rendererAPI->DrawIndexed(vertexArray, indexCount);
		}
	private:
		static Scope<RendererAPI> s_rendererAPI;
	};
}