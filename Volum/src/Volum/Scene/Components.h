#pragma once

#include <glm/glm.hpp>

namespace Volum
{
	enum MeshFilter
	{
		EXTERNAL = 0,

		CUBE = 1,
		SPHERE = 2,
		CYLINDER = 3
	};

	struct TransformComponent
	{
		glm::mat4 Transform { 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform)
			: Transform(transform) {}

		operator glm::mat4& () { return Transform; }
		operator const glm::mat4& () const { return Transform; }
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color { 1.0f };

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: Color(color) {}
	};

	struct MeshComponent
	{
		MeshFilter MeshType = CUBE;

		MeshComponent() = default;
		MeshComponent(const MeshComponent&) = default;
		MeshComponent(const MeshFilter& type)
			: MeshType(type) {}
	};

	struct MaterialComponent
	{
		glm::vec4 Color{ 1.0f };

		MaterialComponent() = default;
		MaterialComponent(const MaterialComponent&) = default;
		MaterialComponent(const glm::vec4& color)
			: Color(color) {}
	};
}