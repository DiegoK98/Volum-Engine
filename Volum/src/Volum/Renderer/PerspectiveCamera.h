#pragma once

#include "Camera.h"

#include <glm/glm.hpp>

namespace Volum
{
	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(float fovY, float aspectRatio, float zNear, float zFar);

		void SetProjection(float fovY, float aspectRatio, float zNear, float zFar);

		void SetPosition(const glm::vec3& position) { m_position = position; RecalculateViewMatrix(); }
		const glm::vec3& GetPosition() const { return m_position; }

		void SetRotation(const glm::vec3& rotation) { m_rotation = rotation; RecalculateViewMatrix(); }
		const glm::vec3& GetRotation() const { return m_rotation; }
	private:
		virtual void RecalculateViewMatrix() override;

		glm::vec3 m_position;
		glm::vec3 m_rotation;
	};
}