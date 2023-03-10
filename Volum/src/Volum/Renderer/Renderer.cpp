#include "vlmpch.h"

#include "Renderer.h"

#include "Volum/Renderer/Renderer2D.h"

namespace Volum
{
	Scope<Renderer::SceneData> Renderer::s_sceneData = CreateScope<Renderer::SceneData>();

	void Renderer::Init()
	{
		VLM_PROFILE_FUNCTION();

		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::Shutdown()
	{
		Renderer2D::Shutdown();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		s_sceneData->viewProjMat = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& modelTransformMat)
	{
		shader->Bind();
		shader->SetMat4("u_viewProjMat", s_sceneData->viewProjMat);
		shader->SetMat4("u_modelMat", modelTransformMat);
		
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}