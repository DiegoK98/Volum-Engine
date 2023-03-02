#include "vlmpch.h"

#include "Application.h"

#include "Volum/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

namespace Volum
{
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		VLM_PROFILE_FUNCTION();

		VLM_CORE_ASSERT(!s_instance, "Application already exists!");
		s_instance = this;

		m_window = Window::Create();
		m_window->SetEventCallback(VLM_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_imGuiLayer = new ImGuiLayer();
		PushOverlay(m_imGuiLayer);
	}

	Application::~Application()
	{
		VLM_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}

	void Application::Run()
	{
		VLM_PROFILE_FUNCTION();

		while (m_running)
		{
			VLM_PROFILE_SCOPE("RunLoop");

			float time = (float)glfwGetTime(); // Temporary. Should be Platform::GetTime()
			TimeStep timeStep = time - m_lastFrameTime;
			m_lastFrameTime = time;

			if (!m_minimized)
			{
				{
					VLM_PROFILE_SCOPE("LayerStack OnUpdate");

					for (Layer* layer : m_layerStack)
						layer->OnUpdate(timeStep);
				}

				m_imGuiLayer->Begin();
				{
					VLM_PROFILE_SCOPE("LayerStack OnImGuiRender");

					for (Layer* layer : m_layerStack)
						layer->OnImGuiRender();
				}
				m_imGuiLayer->End();
			}

			m_window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		VLM_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(VLM_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(VLM_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_layerStack.end(); it != m_layerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		VLM_PROFILE_FUNCTION();

		m_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		VLM_PROFILE_FUNCTION();

		m_layerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_running = false;

		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		VLM_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_minimized = true;
			return false;
		}

		m_minimized = false;

		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}