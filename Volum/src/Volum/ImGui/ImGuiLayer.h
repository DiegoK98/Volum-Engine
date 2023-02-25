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

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

		void SetDarkThemeColors();

	private:
		float m_time = 0.0f;
	};
}