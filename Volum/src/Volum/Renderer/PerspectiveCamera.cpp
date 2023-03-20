#include "vlmpch.h"

#include "PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Volum
{
	PerspectiveCamera::PerspectiveCamera(float fovY, float aspectRatio, float zNear, float zFar)
		: m_projectionMatrix(glm::perspective(glm::radians(fovY), aspectRatio, zNear, zFar)), m_viewMatrix(glm::mat4(1.0f)), m_position(0.0f), m_rotation(0.0f)
	{
		VLM_PROFILE_FUNCTION();

		m_viewProjMatrix = m_projectionMatrix * m_viewMatrix;
	}

	void PerspectiveCamera::SetProjection(float fovY, float aspectRatio, float zNear, float zFar)
	{
		VLM_PROFILE_FUNCTION();

		m_projectionMatrix = glm::perspective(glm::radians(fovY), aspectRatio, zNear, zFar);
		m_viewProjMatrix = m_projectionMatrix * m_viewMatrix;
	}

	void PerspectiveCamera::RecalculateViewMatrix()
	{
		VLM_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f))  // y
			* glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f))  // x
			* glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); // z
		m_viewMatrix = glm::inverse(transform);
		m_viewProjMatrix = m_projectionMatrix * m_viewMatrix;
	}
}