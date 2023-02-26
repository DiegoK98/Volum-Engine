#include "vlmpch.h"

#include "Application.h"

#include "Input.h"
#include "Renderer/Renderer.h"

namespace Volum
{
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		VLM_CORE_ASSERT(!s_instance, "Application already exists!");
		s_instance = this;

		m_window = std::unique_ptr<Window>(Window::Create());
		m_window->SetEventCallback(VLM_BIND_EVENT_FN(Application::OnEvent));

		m_imGuiLayer = new ImGuiLayer();
		PushOverlay(m_imGuiLayer);

		m_vertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f,		0.8f, 0.3f, 0.1f, 1.0f,
			 0.5f, -0.5f, 0.0f,		0.3f, 0.8f, 0.1f, 1.0f,
			 0.0f,  0.5f, 0.0f,		0.6f, 0.1f, 0.6f, 1.0f,
		};

		std::shared_ptr<VertexBuffer> triangleVB;
		triangleVB.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		triangleVB->SetLayout({
			{ ShaderDataType::Float3, "a_position" },
			{ ShaderDataType::Float4, "a_color" }
		});

		m_vertexArray->AddVertexBuffer(triangleVB);

		uint32_t indices[3] = {
			0, 1, 2
		};

		std::shared_ptr<IndexBuffer> triangleIB;
		triangleIB.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_vertexArray->SetIndexBuffer(triangleIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_position;
			layout(location = 1) in vec4 a_color;
			
			out vec3 v_position;
			out vec4 v_color;
			
			void main()
			{
				v_position = a_position * 0.5 + 0.5;
				v_color = a_color;
				gl_Position = vec4(a_position, 1.0);
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
		m_shader.reset(new Shader(vertexSrc, fragmentSrc));

		//////// Blue Square
		float squareVertices[4 * 3] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f,
		};

		m_squareVA.reset(m_squareVA->Create());
		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_position" },
		});

		m_squareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_squareVA->SetIndexBuffer(squareIB);

		std::string vertexSrcBlue = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_position;
			
			out vec3 v_position;
			
			void main()
			{
				v_position = a_position * 0.5 + 0.5;
				gl_Position = vec4(a_position, 1.0);
			}
		)";

		std::string fragmentSrcBlue = R"(
			#version 330 core
			
			in vec3 v_position;
			
			out vec4 color;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		// Equivalent to make_unique
		m_shaderBlue.reset(new Shader(vertexSrcBlue, fragmentSrcBlue));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_running)
		{
			RenderCommand::SetClearColor({ 1.0f, 0.0f, 1.0f, 1.0f });
			RenderCommand::Clear();

			Renderer::BeginScene();

			m_shaderBlue->Bind();
			Renderer::Submit(m_squareVA);
			
			m_shader->Bind();
			Renderer::Submit(m_vertexArray);

			Renderer::EndScene();

			for (Layer* layer : m_layerStack)
				layer->OnUpdate();

			m_imGuiLayer->Begin();

			for (Layer* layer : m_layerStack)
				layer->OnImGuiRender();

			m_imGuiLayer->End();

			m_window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(VLM_BIND_EVENT_FN(Application::OnWindowClose));

		VLM_CORE_TRACE("{0}", e);

		for (auto it = m_layerStack.end(); it != m_layerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_layerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_layerStack.PushOverlay(layer);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_running = false;

		return true;
	}
}