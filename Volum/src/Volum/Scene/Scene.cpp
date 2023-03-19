#include "vlmpch.h"

#include "Scene.h"

#include "Volum/Renderer/Renderer2D.h"
#include "Volum/Renderer/Renderer3D.h"
#include "Entity.h"

#include <glm/glm.hpp>

namespace Volum
{
	Scene::Scene()
	{

	}

	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_registry.create(), this };
		
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>(name);
		tag = name.empty() ? "Unnamed Entity" : name;

		return entity;
	}

	void Scene::OnUpdate(TimeStep ts)
	{
		auto spritesGroup = m_registry.group<SpriteRendererComponent>(entt::get<TransformComponent>);
		for (auto entity : spritesGroup)
		{
			auto [transform, sprite] = spritesGroup.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer3D::DrawQuad(transform, sprite.Color);
		}

		auto cubesGroup = m_registry.group<MeshComponent>(entt::get<TransformComponent, MaterialComponent>);
		for (auto entity : cubesGroup)
		{
			auto [transform, mesh, material] = cubesGroup.get<TransformComponent, MeshComponent, MaterialComponent>(entity);

			if (mesh.MeshType == CUBE)
				Renderer3D::DrawCube(transform, material.Color);
		}
	}
}