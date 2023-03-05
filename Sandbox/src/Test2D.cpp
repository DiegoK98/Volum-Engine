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
	VLM_PROFILE_FUNCTION();

	m_checkerboardTexture = Volum::Texture2D::Create("assets/textures/checkerboard.png");
	m_leavesTexture = Volum::Texture2D::Create("assets/textures/leaves.png");
}

void Test2D::OnDetach()
{
	VLM_PROFILE_FUNCTION();
}

void Test2D::OnUpdate(Volum::TimeStep ts)
{
	VLM_PROFILE_FUNCTION();

	// Update
	m_cameraController.OnUpdate(ts);

	// Render
	Volum::Renderer2D::ResetStats();
	{
		VLM_PROFILE_SCOPE("Renderer Prep");

		Volum::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Volum::RenderCommand::Clear();
	}

	{
		VLM_PROFILE_SCOPE("Renderer Draw");

		static float rotation = 0.0f;
		rotation += ts * 1.0f;

		Volum::Renderer2D::BeginScene(m_cameraController.GetCamera());

		// Opaque objects
		Volum::Renderer2D::DrawQuad({ -1.0f, -1.0f }, { 1.0f, 1.0f }, m_squareColor);
		Volum::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_checkerboardTexture, m_tilingFactor, m_checkerboardTintColor);

		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec3 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f };
				Volum::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, { color, 1.0f });
			}
		}

		// Transparent objects
		Volum::Renderer2D::DrawQuad({ 5.0f, -1.0f, 0.2f }, { 1.0f, 1.0f }, m_leavesTexture);
		Volum::Renderer2D::DrawQuad({ -2.0f, 2.0f, 0.2f }, { 1.0f, 1.0f }, m_leavesTexture);
		Volum::Renderer2D::DrawRotatedQuad({ 4.0f, 0.0f, 0.2f }, rotation, { 1.0f, 1.0f }, m_leavesTexture);
		Volum::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 2.0f, 0.3f }, { 0.2f, 0.6f, 0.1f, 0.6f });

		Volum::Renderer2D::EndScene();
	}
}

void Test2D::OnImGuiRender()
{
	VLM_PROFILE_FUNCTION();

    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square color", glm::value_ptr(m_squareColor));
    ImGui::ColorEdit4("Checkerboard tint color", glm::value_ptr(m_checkerboardTintColor));
    ImGui::DragFloat("Checkerboard tiling factor", &m_tilingFactor, 1.0f, 0.5f, 50.0f);
    ImGui::End();

    ImGui::Begin("Renderer2D Stats");
    auto stats = Volum::Renderer2D::GetStats();
    ImGui::Text("Draw Calls: %d", stats.DrawCallsCount);
    ImGui::Text("Quads: %d", stats.QuadCount);
    ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
    ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
    ImGui::End();
}

void Test2D::OnEvent(Volum::Event& event)
{
	m_cameraController.OnEvent(event);
}