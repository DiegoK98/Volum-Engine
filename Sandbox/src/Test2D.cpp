#include "Test2D.h"

#include <ImGui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

template<typename Fn>
class Timer
{
public:
	Timer(const char* name, Fn&& func)
		: m_Name(name), m_Func(func), m_Stopped(false)
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		if (!m_Stopped)
			Stop();
	}

	void Stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		m_Stopped = true;

		float duration = (end - start) * 0.001f;
		m_Func({ m_Name, duration });
	}
private:
	const char* m_Name;
	Fn m_Func;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	bool m_Stopped;
};

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult) { m_profileResults.push_back(profileResult); })

Test2D::Test2D()
 : Layer("2D Example"), m_cameraController(1280.0f / 720.0f)
{

}

void Test2D::OnAttach()
{
	m_checkerboardTexture = Volum::Texture2D::Create("assets/textures/checkerboard.png");
}

void Test2D::OnDetach()
{

}

void Test2D::OnUpdate(Volum::TimeStep ts)
{
	PROFILE_SCOPE("Test::OnUpdate");

	// Update
	{
		PROFILE_SCOPE("CameraController::OnUpdate");
		m_cameraController.OnUpdate(ts);
	}

	// Render
	{
		PROFILE_SCOPE("Renderer Prep");
		Volum::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Volum::RenderCommand::Clear();
	}

	{
		PROFILE_SCOPE("Renderer Draw");
		Volum::Renderer2D::BeginScene(m_cameraController.GetCamera());
		Volum::Renderer2D::DrawQuad({ 1.5f, -1.0f, -0.2f }, { 1.0f, 1.0f }, m_checkerboardTexture);
		Volum::Renderer2D::DrawQuad({ -1.0f, 1.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Volum::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_checkerboardTexture);
		Volum::Renderer2D::DrawQuad({ 1.0f, -1.0f }, { 2.0f, 0.3f }, { 0.2f, 0.6f, 0.1f, 0.6f });

		Volum::Renderer2D::EndScene();
	}
}

void Test2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square color", glm::value_ptr(m_squareColor));

	for (auto& result : m_profileResults)
	{
		char label[50];
		strcpy(label, "  %.3fms");
		strcat(label, result.Name);
		ImGui::Text(label, result.Time);
	}

	m_profileResults.clear();

	ImGui::End();
}

void Test2D::OnEvent(Volum::Event& event)
{
	m_cameraController.OnEvent(event);
}