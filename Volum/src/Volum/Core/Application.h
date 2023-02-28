#pragma once

#include "Volum/Core/Core.h"
#include "Volum/Core/Window.h"
#include "Volum/Core/LayerStack.h"
#include "Volum/Events/Event.h"
#include "Volum/Events/ApplicationEvent.h"
#include "Volum/ImGui/ImGuiLayer.h"
#include "Volum/Core/TimeStep.h"

namespace Volum
{
	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_window; }

		inline static Application& Get() { return *s_instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		
		std::unique_ptr<Window> m_window;
		ImGuiLayer* m_imGuiLayer;
		bool m_running = true;
		bool m_minimized = false;
		LayerStack m_layerStack;
		float m_lastFrameTime = 0.0f;

		static Application* s_instance;
	};

	// To be defined in a client
	Application* CreateApplication();
}