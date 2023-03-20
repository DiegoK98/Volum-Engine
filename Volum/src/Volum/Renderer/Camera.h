#pragma once

#include <glm/glm.hpp>

namespace Volum
{
	class Camera
	{
	public:
		Camera() = default;
		Camera(glm::mat4 projMat)
			: m_projectionMatrix(projMat) {}
		virtual ~Camera() = default;

		const glm::mat4& GetProjectionMatrix() const { return m_projectionMatrix; }
	protected:
		glm::mat4 m_projectionMatrix = glm::mat4(1.0f);
	};
}