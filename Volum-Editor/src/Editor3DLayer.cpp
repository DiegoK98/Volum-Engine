#include "Editor3DLayer.h"

#include <ImGui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Volum
{
	Editor3DLayer::Editor3DLayer()
		: Layer("Editor 3D Layer"), m_cameraController(45.0f, 1280.0f / 720.0f)
	{

	}

	void Editor3DLayer::OnAttach()
	{
		VLM_PROFILE_FUNCTION();

		m_checkerboardTexture = Texture2D::Create("assets/textures/checkerboard.png");
		m_leavesTexture = Texture2D::Create("assets/textures/leaves.png");

		FramebufferSpecification framebufferSpec;
		framebufferSpec.Width = 1280;
		framebufferSpec.Height = 720;

		m_framebuffer = Framebuffer::Create(framebufferSpec);

		m_activeScene = CreateRef<Scene>();

		m_cubeEntity = m_activeScene->CreateEntity("Color-changing Cube");
		m_cubeEntity.AddComponent<MeshComponent>(CUBE);
		m_cubeEntity.AddComponent<MaterialComponent>(m_cubeColor);
	}

	void Editor3DLayer::OnDetach()
	{
		VLM_PROFILE_FUNCTION();
	}

	void Editor3DLayer::OnUpdate(TimeStep ts)
	{
		VLM_PROFILE_FUNCTION();

		// Resize
		if (FramebufferSpecification spec = m_framebuffer->GetSpecification();
			m_viewportSize.x > 0.0f && m_viewportSize.y > 0.0f && // zero sized framebuffer is invalid
			(spec.Width != m_viewportSize.x || spec.Height != m_viewportSize.y))
		{
			m_framebuffer->Resize((uint32_t)m_viewportSize.x, (uint32_t)m_viewportSize.y);
			m_cameraController.Resize(m_viewportSize.x, m_viewportSize.y);
		}

		if (m_viewportFocused)
			m_cameraController.OnUpdate(ts);
		
		// Draw preparation
		Renderer3D::ResetStats();

		m_framebuffer->Bind();
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();
		
		// Draw
		Renderer3D::BeginScene(m_cameraController.GetCamera());

		// Update scene
		m_activeScene->OnUpdate(ts);

		// End of draw
		Renderer3D::EndScene();
		m_framebuffer->Unbind();
	}

	void Editor3DLayer::OnImGuiRender()
	{
		VLM_PROFILE_FUNCTION();

		static bool p_open = true;
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->GetWorkPos());
			ImGui::SetNextWindowSize(viewport->GetWorkSize());
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		ImGui::Begin("Editor Dockspace", &p_open, window_flags);

		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiID dockspace_id = ImGui::GetID("EditorDockspace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit")) Application::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::Begin("Settings");
		if (m_cubeEntity)
		{
			ImGui::Separator();
			ImGui::Text("%s", m_cubeEntity.GetComponent<TagComponent>().Tag.c_str());

			auto& cubeColor = m_cubeEntity.GetComponent<MaterialComponent>().Color;
			ImGui::ColorEdit4("Cube color", glm::value_ptr(cubeColor));
		}

		ImGui::Separator();
		ImGui::Text("Other properties");
		ImGui::ColorEdit4("Checkerboard tint color", glm::value_ptr(m_checkerboardTintColor));
		ImGui::DragFloat("Checkerboard tiling factor", &m_tilingFactor, 1.0f, 0.5f, 50.0f);
		ImGui::End();

		ImGui::Begin("Renderer3D Stats");
		auto stats = Renderer3D::GetStats();
		ImGui::Text("Draw Calls: %d", stats.DrawCallsCount);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Cubes: %d", stats.CubeCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("Scene View");

		m_viewportFocused = ImGui::IsWindowFocused();
		m_viewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!m_viewportHovered); // Only let events through if hovering

		if (!m_viewportHovered)
			m_cameraController.SetCursorMoveCamera(false);

		ImVec2 panelSize = ImGui::GetContentRegionAvail();
		m_viewportSize = { panelSize.x, panelSize.y };

		auto textureID = (uint16_t)m_framebuffer->GetColorAttachmentRendererID(); // Cast to 16bits to eliminate a warning
		ImGui::Image((void*)textureID, panelSize, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();
		ImGui::PopStyleVar(ImGuiStyleVar_WindowPadding);

		ImGui::End();
	}

	void Editor3DLayer::OnEvent(Event& event)
	{
		m_cameraController.OnEvent(event);
	}
}