#include "vlmpch.h"

#include "Renderer.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Volum
{
	Renderer::SceneData* Renderer::s_sceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		RenderCommand::Init();
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
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_viewProjMat", s_sceneData->viewProjMat);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_modelMat", modelTransformMat);
		
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}