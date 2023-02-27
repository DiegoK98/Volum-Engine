#include <Volum.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include <ImGui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Volum::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_camera(Volum::OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f)), m_cameraPosition(0.0f),
		m_trianglePosition(0.0f)
	{
		m_vertexArray.reset(Volum::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.388f, 0.0f,		0.8f, 0.3f, 0.1f, 1.0f,
			 0.5f, -0.388f, 0.0f,		0.3f, 0.8f, 0.1f, 1.0f,
			 0.0f,  0.477f, 0.0f,		0.6f, 0.1f, 0.6f, 1.0f,
		};

		std::shared_ptr<Volum::VertexBuffer> triangleVB;
		triangleVB.reset(Volum::VertexBuffer::Create(vertices, sizeof(vertices)));

		triangleVB->SetLayout({
			{ Volum::ShaderDataType::Float3, "a_position" },
			{ Volum::ShaderDataType::Float4, "a_color" }
			});

		m_vertexArray->AddVertexBuffer(triangleVB);

		uint32_t indices[3] = {
			0, 1, 2
		};

		std::shared_ptr<Volum::IndexBuffer> triangleIB;
		triangleIB.reset(Volum::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_vertexArray->SetIndexBuffer(triangleIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_position;
			layout(location = 1) in vec4 a_color;
			
			uniform mat4 u_viewProjMat;
			uniform mat4 u_modelMat;
			
			out vec3 v_position;
			out vec4 v_color;
			
			void main()
			{
				v_position = a_position * 0.5 + 0.5;
				v_color = a_color;
				gl_Position = u_viewProjMat * u_modelMat * vec4(a_position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			
			in vec3 v_position;
			in vec4 v_color;
			
			out vec4 color;

			void main()
			{
				color = v_color;
			}
		)";

		// Equivalent to make_unique
		m_shader.reset(Volum::Shader::Create(vertexSrc, fragmentSrc));

		//////// Blue Square
		float squareVertices[4 * 3] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f,
		};

		m_squareVA.reset(m_squareVA->Create());
		std::shared_ptr<Volum::VertexBuffer> squareVB;
		squareVB.reset(Volum::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ Volum::ShaderDataType::Float3, "a_position" },
			});

		m_squareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		std::shared_ptr<Volum::IndexBuffer> squareIB;
		squareIB.reset(Volum::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_squareVA->SetIndexBuffer(squareIB);

		std::string vertexSrcColor = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_position;
			
			uniform mat4 u_viewProjMat;
			uniform mat4 u_modelMat;
			
			out vec3 v_position;
			
			void main()
			{
				v_position = a_position * 0.5 + 0.5;
				gl_Position = u_viewProjMat * u_modelMat * vec4(a_position, 1.0);
			}
		)";

		std::string fragmentSrcColor = R"(
			#version 330 core
			
			in vec3 v_position;
			
			uniform vec3 u_color;
			
			out vec4 color;

			void main()
			{
				color = vec4(u_color, 1.0);
			}
		)";

		// Equivalent to make_unique
		m_shaderColor.reset(Volum::Shader::Create(vertexSrcColor, fragmentSrcColor));
	}

	void OnUpdate(Volum::TimeStep ts) override
	{
		VLM_TRACE("Delta time: {0}ms", ts.GetMiliseconds());

		// Move inputs
		if (Volum::Input::isKeyPressed(VLM_KEY_A))
			m_cameraPosition.x -= m_cameraMoveSpeed * ts;
		else if (Volum::Input::isKeyPressed(VLM_KEY_D))
			m_cameraPosition.x += m_cameraMoveSpeed * ts;
		else if (Volum::Input::isKeyPressed(VLM_KEY_W))
			m_cameraPosition.y += m_cameraMoveSpeed * ts;
		else if (Volum::Input::isKeyPressed(VLM_KEY_S))
			m_cameraPosition.y -= m_cameraMoveSpeed * ts;

		// Rotation inputs
		if (Volum::Input::isKeyPressed(VLM_KEY_Q))
			m_cameraRotation += m_cameraRotationSpeed * ts;
		else if (Volum::Input::isKeyPressed(VLM_KEY_E))
			m_cameraRotation -= m_cameraRotationSpeed * ts;

		// Triangle moving inputs
		if (Volum::Input::isKeyPressed(VLM_KEY_LEFT))
			m_trianglePosition.x -= m_triangleMoveSpeed * ts;
		else if (Volum::Input::isKeyPressed(VLM_KEY_RIGHT))
			m_trianglePosition.x += m_triangleMoveSpeed * ts;
		else if (Volum::Input::isKeyPressed(VLM_KEY_UP))
			m_trianglePosition.y += m_triangleMoveSpeed * ts;
		else if (Volum::Input::isKeyPressed(VLM_KEY_DOWN))
			m_trianglePosition.y -= m_triangleMoveSpeed * ts;

		// Renderer
		Volum::RenderCommand::SetClearColor({ 1.0f, 0.0f, 1.0f, 1.0f });
		Volum::RenderCommand::Clear();

		m_camera.SetPosition(m_cameraPosition);
		m_camera.SetRotation(m_cameraRotation);

		Volum::Renderer::BeginScene(m_camera);

		glm::mat4 triangleTransform = glm::translate(glm::mat4(1.0f), m_trianglePosition);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		glm::vec4 blueColor(0.3f, 0.2f, 0.8f, 1.0f);
		glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);

		m_shaderColor->Bind();
		std::dynamic_pointer_cast<Volum::OpenGLShader>(m_shaderColor)->UploadUniformFloat3("u_color", m_squareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.18f, y * 0.18f, 0.0f);
				glm::mat4 squareTransform = glm::translate(glm::mat4(1.0f), pos) * scale;

				Volum::Renderer::Submit(m_shaderColor, m_squareVA, squareTransform);
			}
		}

		Volum::Renderer::Submit(m_shader, m_vertexArray, triangleTransform);

		Volum::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		
		ImGui::ColorEdit3("Square color", glm::value_ptr(m_squareColor));
		
		ImGui::End();
	}

	void OnEvent(Volum::Event& event) override
	{
	}

private:
	std::shared_ptr<Volum::VertexArray> m_vertexArray;
	std::shared_ptr<Volum::Shader> m_shader;

	std::shared_ptr<Volum::VertexArray> m_squareVA;
	std::shared_ptr<Volum::Shader> m_shaderColor;

	Volum::OrthographicCamera m_camera;
	glm::vec3 m_cameraPosition;
	float m_cameraRotation = 0.0f;
	float m_cameraMoveSpeed = 3.0f;
	float m_cameraRotationSpeed = 90.0f;

	glm::vec3 m_trianglePosition;
	float m_triangleMoveSpeed = 1.0f;

	glm::vec3 m_squareColor = { 0.3f, 0.2f, 0.8f };
};

class Example : public Volum::Application
{
public:
	Example()
	{
		PushLayer(new ExampleLayer());
	}

	~Example()
	{

	}
};

Volum::Application* Volum::CreateApplication()
{
	VLM_WARN("This is an example");

	return new Example();
}