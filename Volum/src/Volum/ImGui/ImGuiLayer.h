#pragma once

#include "Volum/Core/Layer.h"
#include "Volum/Events/ApplicationEvent.h"
#include "Volum/Events/MouseEvent.h"
#include "Volum/Events/KeyEvent.h"

namespace Volum
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_blockEvents = block; }
		
		void SetDarkThemeColors();

	private:
		bool m_blockEvents = true;
		float m_time = 0.0f;
	};
}