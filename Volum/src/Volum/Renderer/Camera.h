#pragma once

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>

namespace Volum
{
	class Camera
	{
	public:
		Camera() = default;
		Camera(glm::mat4 projMat)
			: m_projectionMatrix(projMat) {}

		const glm::mat4& GetProjectionMatrix() const { return m_projectionMatrix; }
	private:
		glm::mat4 m_projectionMatrix;
	};
}