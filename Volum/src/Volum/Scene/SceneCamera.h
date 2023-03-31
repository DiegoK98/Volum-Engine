#pragma once

#include "Volum/Renderer/Camera.h"

namespace Volum
{
	class SceneCamera : public Camera
	{
	public:
		enum class ProjectionType { Perspective = 0, Orthographic = 1 };

		SceneCamera();
		virtual ~SceneCamera() = default;

		void SetPerspective(float fovY, float nearClip, float farClip);
		void SetOrthographic(float size, float nearClip, float farClip);

		void SetViewportSize(uint32_t width, uint32_t height);

		ProjectionType GetProjectionType() { return m_projectionType; }
		void SetProjectionType(ProjectionType type) { m_projectionType = type; RecalculateProjection(); }

		float GetPerspectiveFovY() { return glm::degrees(m_perspectiveFovY); }
		void SetPerspectiveFovY(float fovY) { m_perspectiveFovY = glm::radians(fovY); RecalculateProjection(); }

		float GetPerspectiveNear() { return m_perspectiveNear; }
		float GetPerspectiveFar() { return m_perspectiveFar; }
		void SetPerspectiveNear(float nearClip) { m_perspectiveNear = nearClip; RecalculateProjection(); }
		void SetPerspectiveFar(float farClip) { m_perspectiveFar = farClip; RecalculateProjection(); }

		float GetOrthographicSize() { return m_orthographicSize; }
		void SetOrthographicSize(float size) { m_orthographicSize = size; RecalculateProjection(); }

		float GetOrthographicNear() { return m_orthographicNear; }
		float GetOrthographicFar() { return m_orthographicFar; }
		void SetOrthographicNear(float nearClip) { m_orthographicNear = nearClip; RecalculateProjection(); }
		void SetOrthographicFar(float farClip) { m_orthographicFar = farClip; RecalculateProjection(); }

	private:
		void RecalculateProjection();

		#if VLM_RENDERER_3D
			ProjectionType m_projectionType = ProjectionType::Perspective;
		#else
			ProjectionType m_projectionType = ProjectionType::Orthographic;
		#endif
		
		float m_aspectRatio = 0.0f;

		float m_perspectiveFovY = glm::radians(45.0f);
		float m_perspectiveNear = 0.1f, m_perspectiveFar = 1000.0f;

		float m_orthographicSize = 10.0f;
		float m_orthographicNear = -1.0f, m_orthographicFar = 10.0f;
	};
}
