#pragma once

#include "Volum/Layer.h"
#include "Volum/Events/ApplicationEvent.h"
#include "Volum/Events/MouseEvent.h"
#include "Volum/Events/KeyEvent.h"

namespace Volum
{
	class VOLUM_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);

		void SetDarkThemeColors();
	private:
		// Not necessary (modern ImGui versions already have all this)
		/*bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);*/

		float m_time = 0.0f;
	};
}