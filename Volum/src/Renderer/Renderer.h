#pragma once

#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace Volum
{
	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);
		static void EndScene();

		static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); };
	private:
		struct SceneData
		{
			glm::mat4 viewProjMat;
		};

		static SceneData* m_sceneData;
	};
}