#pragma once

#include "Volum/Core/Base.h"
#include "Volum/Core/Window.h"
#include "Volum/Core/LayerStack.h"
#include "Volum/Events/Event.h"
#include "Volum/Events/ApplicationEvent.h"
#include "Volum/ImGui/ImGuiLayer.h"
#include "Volum/Core/TimeStep.h"

int main(int argc, char** argv);

namespace Volum
{
	class Application
	{
	public:
		Application(const std::string& name = "Volum App");
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		Window& GetWindow() { return *m_window; }

		void Close() { m_running = false; };

		static Application& Get() { return *s_instance; }
	private:
		void Run();

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		
		Scope<Window> m_window;
		ImGuiLayer* m_imGuiLayer;
		bool m_running = true;
		bool m_minimized = false;
		LayerStack m_layerStack;
		float m_lastFrameTime = 0.0f;

		static Application* s_instance;
		friend int ::main(int argc, char** argv);
	};

	// To be defined in a client
	Application* CreateApplication();
}