#include "vlmpch.h"

#include "Renderer.h"
#include "RenderCommand.h"

namespace Volum
{
	Renderer::SceneData* Renderer::m_sceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_sceneData->viewProjMat = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_viewProjMat", m_sceneData->viewProjMat);
		
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}