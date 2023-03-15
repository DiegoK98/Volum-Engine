#pragma once

#include "Camera.h"

#include <glm/glm.hpp>

namespace Volum
{
	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		void SetProjection(float left, float right, float bottom, float top);

		void SetPosition(const glm::vec3& position) { m_position = position; RecalculateViewMatrix(); }
		const glm::vec3& GetPosition() const { return m_position; }

		void SetRotation(const float rotation) { m_rotation = rotation; RecalculateViewMatrix(); }
		const float GetRotation() const { return m_rotation; }
	private:
		virtual void RecalculateViewMatrix() override;

		glm::vec3 m_position;
		float m_rotation = 0.0f;
	};
}