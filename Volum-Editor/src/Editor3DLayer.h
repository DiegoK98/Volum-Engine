#pragma once

#include <Volum.h>

namespace Volum
{
	class Editor3DLayer : public Layer
	{
	public:
		Editor3DLayer();
		virtual ~Editor3DLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(TimeStep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;

	private:
		OrthographicCameraController m_cameraController;

		// Temp
		Ref<VertexArray> m_squareVA;
		Ref<Shader> m_flatColorShader;
		Ref<Framebuffer> m_framebuffer;

		Ref<Texture2D> m_checkerboardTexture;
		Ref<Texture2D> m_leavesTexture;

		bool m_viewportFocused = false;
		bool m_viewportHovered = false;
		glm::vec2 m_viewportSize = { 0.0f, 0.0f };

		glm::vec4 m_squareColor = { 0.3f, 0.2f, 0.8f, 1.0f };
		glm::vec4 m_checkerboardTintColor = { 0.8f, 0.2f, 0.3f, 1.0f };
		float m_tilingFactor = 1.0f;
	};
}