#include "vlmpch.h"

#include "SceneCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Volum
{
	SceneCamera::SceneCamera()
	{
		RecalculateProjection();
	}

	void SceneCamera::SetPerspective(float fovY, float nearClip, float farClip)
	{
		m_projectionType = ProjectionType::Perspective;

		m_perspectiveFovY = glm::radians(fovY);
		m_perspectiveNear = nearClip;
		m_perspectiveFar = farClip;

		RecalculateProjection();
	}

	void SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
	{
		m_projectionType = ProjectionType::Orthographic;

		m_orthographicSize = size;
		m_orthographicNear = nearClip;
		m_orthographicFar = farClip;

		RecalculateProjection();
	}

	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		const float newAspecRatio = (float)width / (float)height;
		if (m_aspectRatio == newAspecRatio)
			return;

		m_aspectRatio = newAspecRatio;
		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection()
	{
		if (m_projectionType == ProjectionType::Perspective)
		{
			m_projectionMatrix = glm::perspective(m_perspectiveFovY, m_aspectRatio, m_perspectiveNear, m_perspectiveFar);
		}
		else
		{
			float orthoLeft = -0.5f * m_aspectRatio * m_orthographicSize;
			float orthoRight = 0.5f * m_aspectRatio * m_orthographicSize;
			float orthoBottom = -0.5f * m_orthographicSize;
			float orthoTop = 0.5f * m_orthographicSize;

			m_projectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, m_orthographicNear, m_orthographicFar);
		}
	}
}
