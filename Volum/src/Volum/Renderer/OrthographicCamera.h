#pragma once

#include <glm/glm.hpp>

namespace Volum
{
	// TODO: Create a base class for Cameras
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		const glm::mat4& GetViewMatrix() const { return m_viewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_viewProjMatrix; }

		void SetProjection(float left, float right, float bottom, float top);

		void SetPosition(const glm::vec3& position) { m_position = position; RecalculateViewMatrix(); }
		const glm::vec3& GetPosition() const { return m_position; }

		void SetRotation(const float rotation) { m_rotation = rotation; RecalculateViewMatrix(); }
		const float GetRotation() const { return m_rotation; }
	private:
		void RecalculateViewMatrix();

		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewMatrix;
		glm::mat4 m_viewProjMatrix;

		glm::vec3 m_position;
		float m_rotation = 0.0f;
	};
}