#pragma once

#include <glm/glm.hpp>

namespace Volum
{
	// TODO: Create a base class for Cameras
	class PerspectiveCamera
	{
	public:
		PerspectiveCamera(float fovY, float aspectRatio, float zNear, float zFar);

		const glm::mat4& GetViewMatrix() const { return m_viewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_viewProjMatrix; }

		void SetProjection(float fovY, float aspectRatio, float zNear, float zFar);

		void SetPosition(const glm::vec3& position) { m_position = position; RecalculateViewMatrix(); }
		const glm::vec3& GetPosition() const { return m_position; }

		void SetRotation(const glm::vec3& rotation) { m_rotation = rotation; RecalculateViewMatrix(); }
		const glm::vec3& GetRotation() const { return m_rotation; }
	private:
		void RecalculateViewMatrix();

		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewMatrix;
		glm::mat4 m_viewProjMatrix;

		glm::vec3 m_position;
		glm::vec3 m_rotation;
	};
}