#include "vlmpch.h"

#include "Application.h"

#include "Input.h"

#include <glad/gl.h>

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
	}
	
	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_running)
		{
			glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

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