#pragma once

#include "Volum/Renderer/Camera.h"

namespace Volum
{
	class SceneCamera : public Camera
	{
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;

		void SetOrthographic(float size, float nearClip, float farClip);
		void SetPerspective(float fovY, float nearClip, float farClip);

		void SetViewportSize(uint32_t width, uint32_t height);

	private:
		void RecalculateProjection();

		#if VLM_RENDERER_3D
			bool m_isPerspective = true;
		#else
			bool m_isPerspective = false;
		#endif
		
		float m_aspectRatio = 0.0f;

		float m_orthographicSize = 10.0f;
		float m_orthographicNear = -1.0f, m_orthographicFar = 1.0f;

		float m_perspectiveFovY = 45.0f;
		float m_perspectiveNear = 0.1f, m_perspectiveFar = 1000.0f;
	};
}