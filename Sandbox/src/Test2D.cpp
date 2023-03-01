#include "Test2D.h"

#include <ImGui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Test2D::Test2D()
 : Layer("2D Example"), m_cameraController(1280.0f / 720.0f)
{

}

void Test2D::OnAttach()
{

}

void Test2D::OnDetach()
{

}

void Test2D::OnUpdate(Volum::TimeStep ts)
{
	// Update
	m_cameraController.OnUpdate(ts);

	// Render
	Volum::RenderCommand::SetClearColor({ 1.0f, 0.0f, 1.0f, 1.0f });
	Volum::RenderCommand::Clear();

	Volum::Renderer2D::BeginScene(m_cameraController.GetCamera());

	//m_flatColorShader->Bind();
	//m_flatColorShader->UploadUniformFloat4("u_color", m_squareColor);
	//Volum::Renderer::Submit(m_flatColorShader, m_squareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Volum::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });

	Volum::Renderer2D::EndScene();
}

void Test2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square color", glm::value_ptr(m_squareColor));
	ImGui::End();
}

void Test2D::OnEvent(Volum::Event& event)
{
	m_cameraController.OnEvent(event);
}