#pragma once

#include <Volum.h>

class Test2D : public Volum::Layer
{
public:
	Test2D();
	virtual ~Test2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Volum::TimeStep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Volum::Event& event) override;
private:
	Volum::OrthographicCameraController m_cameraController;

	// Temp
	Volum::Ref<Volum::VertexArray> m_squareVA;
	Volum::Ref<Volum::Shader> m_flatColorShader;

	Volum::Ref<Volum::Texture2D> m_checkerboardTexture;

	struct ProfileResult
	{
		const char* Name;
		float Time;
	};

	std::vector<ProfileResult> m_profileResults;

	glm::vec4 m_squareColor = { 0.3f, 0.2f, 0.8f, 1.0f };
};