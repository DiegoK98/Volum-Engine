#pragma once

#include <Volum.h>

class TestLayer : public Volum::Layer
{
public:
	TestLayer();
	virtual ~TestLayer() = default;

	virtual void OnUpdate(Volum::TimeStep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Volum::Event& event) override;

private:
	Volum::ShaderLibrary m_shaderLibrary;
	Volum::Ref<Volum::VertexArray> m_vertexArray;
	Volum::Ref<Volum::Shader> m_shader;

	Volum::Ref<Volum::VertexArray> m_squareVA;
	Volum::Ref<Volum::Shader> m_shaderFlatColor;

	Volum::Ref<Volum::Texture2D> m_texture;
	Volum::Ref<Volum::Texture2D> m_textureLeaves;

	Volum::Camera2DController m_cameraController;

	glm::vec3 m_trianglePosition = { 0.0f, 0.0f, 0.0f };
	float m_triangleMoveSpeed = 1.0f;

	glm::vec3 m_squareColor = { 0.3f, 0.2f, 0.8f };
};