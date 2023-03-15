#pragma once

#include <glm/glm.hpp>

namespace Volum
{
	class Camera
	{
	public:
		Camera(glm::mat4 projMat, glm::mat4 viewMat)
			: m_projectionMatrix(projMat), m_viewMatrix(viewMat)
		{
			VLM_PROFILE_FUNCTION();

			m_viewProjMatrix = m_projectionMatrix * m_viewMatrix;
		}

		const glm::mat4& GetProjectionMatrix() const { return m_projectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_viewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_viewProjMatrix; }
	protected:
		virtual void RecalculateViewMatrix() = 0;

		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewMatrix;
		glm::mat4 m_viewProjMatrix;
	};
}