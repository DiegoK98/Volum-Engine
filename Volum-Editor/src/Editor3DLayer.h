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
		// Temp
		Ref<VertexArray> m_squareVA;
		Ref<Shader> m_flatColorShader;
		Ref<Framebuffer> m_framebuffer;

		Ref<Scene> m_activeScene;

		Entity m_cubeEntity;
		Entity m_mainCameraEntity;
		Entity m_secondCameraEntity;

		Ref<Texture2D> m_checkerboardTexture;
		Ref<Texture2D> m_leavesTexture;

		bool m_secondCamera = false;

		glm::vec2 m_viewportSize = { 0.0f, 0.0f };

		const glm::vec4 m_cubeColor = { 0.6f, 0.1f, 0.8f, 0.5f };
		glm::vec4 m_checkerboardTintColor = { 0.8f, 0.2f, 0.3f, 1.0f };
		float m_tilingFactor = 1.0f;
	};
}
