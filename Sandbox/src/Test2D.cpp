#include "Test2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include <ImGui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Test2D::Test2D()
 : Layer("2D Example"), m_cameraController(1280.0f / 720.0f)
{

}

void Test2D::OnAttach()
{
	//////// Blue Square
	m_squareVA = Volum::VertexArray::Create();

	float squareVertices[4 * 3] = {
		-0.75f, -0.75f, 0.0f,
		 0.75f, -0.75f, 0.0f,
		 0.75f,  0.75f, 0.0f,
		-0.75f,  0.75f, 0.0f,
	};

	Volum::Ref<Volum::VertexBuffer> squareVB;
	squareVB = Volum::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

	squareVB->SetLayout({
		{ Volum::ShaderDataType::Float3, "a_position" },
		});

	m_squareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	Volum::Ref<Volum::IndexBuffer> squareIB;
	squareIB = Volum::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_squareVA->SetIndexBuffer(squareIB);

	m_flatColorShader = Volum::Shader::Create("assets/shaders/FlatColor.glsl");
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

	Volum::Renderer::BeginScene(m_cameraController.GetCamera());

	m_flatColorShader->Bind();
	std::dynamic_pointer_cast<Volum::OpenGLShader>(m_flatColorShader)->UploadUniformFloat4("u_color", m_squareColor);

	Volum::Renderer::Submit(m_flatColorShader, m_squareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Volum::Renderer::EndScene();
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