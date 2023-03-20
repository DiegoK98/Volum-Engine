#include "vlmpch.h"

#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Volum
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_projectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_viewMatrix(glm::mat4(1.0f)), m_position(0.0f)
	{
		VLM_PROFILE_FUNCTION();

		m_viewProjMatrix = m_projectionMatrix * m_viewMatrix;
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		VLM_PROFILE_FUNCTION();

		m_projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_viewProjMatrix = m_projectionMatrix * m_viewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		VLM_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		m_viewMatrix = glm::inverse(transform);
		m_viewProjMatrix = m_projectionMatrix * m_viewMatrix;
	}
}