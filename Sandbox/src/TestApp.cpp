#include <Volum.h>
#include <Volum/Core/EntryPoint.h>

#include <ImGui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Test2D.h"

class TestLayer : public Volum::Layer
{
public:
	TestLayer()
		: Layer("Example"), m_cameraController(1280.0f / 720.0f, true)
	{
		m_vertexArray = Volum::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.388f, 0.0f,		0.8f, 0.3f, 0.1f, 1.0f,
			 0.5f, -0.388f, 0.0f,		0.3f, 0.8f, 0.1f, 1.0f,
			 0.0f,  0.477f, 0.0f,		0.6f, 0.1f, 0.6f, 1.0f,
		};

		Volum::Ref<Volum::VertexBuffer> triangleVB;
		triangleVB = Volum::VertexBuffer::Create(vertices, sizeof(vertices));

		triangleVB->SetLayout({
			{ Volum::ShaderDataType::Float3, "a_position" },
			{ Volum::ShaderDataType::Float4, "a_color" }
		});

		m_vertexArray->AddVertexBuffer(triangleVB);

		uint32_t indices[3] = {
			0, 1, 2
		};

		Volum::Ref<Volum::IndexBuffer> triangleIB;
		triangleIB = Volum::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_vertexArray->SetIndexBuffer(triangleIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_position;
			layout(location = 1) in vec4 a_color;
			
			uniform mat4 u_viewProjMat;
			uniform mat4 u_modelMat;
			
			out vec4 v_color;
			
			void main()
			{
				v_color = a_color;
				gl_Position = u_viewProjMat * u_modelMat * vec4(a_position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			in vec4 v_color;
			
			out vec4 color;

			void main()
			{
				color = v_color;
			}
		)";

		// Equivalent to make_unique
		m_shader = Volum::Shader::Create("VertexColor", vertexSrc, fragmentSrc);

		//////// Blue Square
		float squareVertices[4 * 5] = {
			-0.75f, -0.75f, 0.0f,		0.0f, 0.0f,
			 0.75f, -0.75f, 0.0f,		1.0f, 0.0f,
			 0.75f,  0.75f, 0.0f,		1.0f, 1.0f,
			-0.75f,  0.75f, 0.0f,		0.0f, 1.0f,
		};

		m_squareVA = m_squareVA->Create();
		Volum::Ref<Volum::VertexBuffer> squareVB;
		squareVB = Volum::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

		squareVB->SetLayout({
			{ Volum::ShaderDataType::Float3, "a_position" },
			{ Volum::ShaderDataType::Float2, "a_texCoords" },
		});

		m_squareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		Volum::Ref<Volum::IndexBuffer> squareIB;
		squareIB = Volum::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_squareVA->SetIndexBuffer(squareIB);

		std::string vertexSrcFlatColor = R"(
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

		std::string fragmentSrcFlatColor = R"(
			#version 330 core
			
			in vec3 v_position;
			
			uniform vec3 u_color;
			
			out vec4 color;

			void main()
			{
				color = vec4(u_color, 1.0);
			}
		)";

		m_shaderFlatColor = Volum::Shader::Create("FlatColor", vertexSrcFlatColor, fragmentSrcFlatColor);

		auto texture_shader = m_shaderLibrary.Load("assets/shaders/Texture.glsl");

		m_texture = Volum::Texture2D::Create("assets/textures/checkerboard.png");
		m_textureLeaves = Volum::Texture2D::Create("assets/textures/leaves.png");

		texture_shader->Bind();
		texture_shader->UploadUniformInt("u_texture", 0);
	}

	void OnUpdate(Volum::TimeStep ts) override
	{
		////// Update loop //////
		m_cameraController.OnUpdate(ts);

		// Triangle moving inputs
		if (Volum::Input::IsKeyPressed(VLM_KEY_LEFT))
			m_trianglePosition.x -= m_triangleMoveSpeed * ts;
		else if (Volum::Input::IsKeyPressed(VLM_KEY_RIGHT))
			m_trianglePosition.x += m_triangleMoveSpeed * ts;
		else if (Volum::Input::IsKeyPressed(VLM_KEY_UP))
			m_trianglePosition.y += m_triangleMoveSpeed * ts;
		else if (Volum::Input::IsKeyPressed(VLM_KEY_DOWN))
			m_trianglePosition.y -= m_triangleMoveSpeed * ts;

		////// Render loop //////
		Volum::RenderCommand::SetClearColor({ 1.0f, 0.0f, 1.0f, 1.0f });
		Volum::RenderCommand::Clear();

		Volum::Renderer::BeginScene(m_cameraController.GetCamera());

		glm::mat4 triangleTransform = glm::translate(glm::mat4(1.0f), m_trianglePosition);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		glm::vec4 blueColor(0.3f, 0.2f, 0.8f, 1.0f);
		glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);

		m_shaderFlatColor->Bind();
		m_shaderFlatColor->UploadUniformFloat3("u_color", m_squareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.18f, y * 0.18f, 0.0f);
				glm::mat4 squareTransform = glm::translate(glm::mat4(1.0f), pos) * scale;

				Volum::Renderer::Submit(m_shaderFlatColor, m_squareVA, squareTransform);
			}
		}

		auto textureShader = m_shaderLibrary.Get("Texture");

		m_texture->Bind();
		Volum::Renderer::Submit(textureShader, m_squareVA, triangleTransform);
		m_textureLeaves->Bind();
		Volum::Renderer::Submit(textureShader, m_squareVA, triangleTransform);

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
		m_cameraController.OnEvent(event);
	}

private:
	Volum::ShaderLibrary m_shaderLibrary;
	Volum::Ref<Volum::VertexArray> m_vertexArray;
	Volum::Ref<Volum::Shader> m_shader;

	Volum::Ref<Volum::VertexArray> m_squareVA;
	Volum::Ref<Volum::Shader> m_shaderFlatColor;

	Volum::Ref<Volum::Texture2D> m_texture;
	Volum::Ref<Volum::Texture2D> m_textureLeaves;

	Volum::OrthographicCameraController m_cameraController;

	glm::vec3 m_trianglePosition = { 0.0f, 0.0f, 0.0f };
	float m_triangleMoveSpeed = 1.0f;

	glm::vec3 m_squareColor = { 0.3f, 0.2f, 0.8f };
};

class Test : public Volum::Application
{
public:
	Test()
	{
		//PushLayer(new TestLayer());
		PushLayer(new Test2D());
	}

	~Test()
	{

	}
};

Volum::Application* Volum::CreateApplication()
{
	VLM_WARN("Created Test application");

	return new Test();
}