#pragma once

#include "Volum/Renderer/RenderCommand.h"
#include "Volum/Renderer/OrthographicCamera.h"
#include "Volum/Renderer/Shader.h"

namespace Volum
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();
		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(OrthographicCamera& camera);
		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
		static void EndScene();

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); };
	private:
		struct SceneData
		{
			glm::mat4 viewProjMat;
		};

		static Scope<SceneData> s_sceneData;
	};
}