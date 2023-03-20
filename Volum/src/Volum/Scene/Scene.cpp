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
		Camera* mainCamera = nullptr;
		glm::mat4* cameraTransform;
		{
			auto group = m_registry.group<CameraComponent>(entt::get<TransformComponent>);
			for (auto entity : group)
			{
				auto [transform, camera] = group.get<TransformComponent, CameraComponent>(entity);

				if (camera.Main)
				{
					mainCamera = &camera.Camera;
					cameraTransform = &transform.Transform;
					break;
				}
			}
		}

		if (mainCamera)
		{
			Renderer3D::BeginScene(*mainCamera, *cameraTransform);

			// Render sprites
			{
				auto group = m_registry.group<SpriteRendererComponent>(entt::get<TransformComponent>);
				for (auto entity : group)
				{
					auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

					Renderer3D::DrawQuad(transform, sprite.Color);
				}
			}

			// Render meshes
			{
				auto group = m_registry.group<MeshComponent, MaterialComponent>(entt::get<TransformComponent>);
				for (auto entity : group)
				{
					auto [transform, mesh, material] = group.get<TransformComponent, MeshComponent, MaterialComponent>(entity);

					if (mesh.MeshType == CUBE)
						Renderer3D::DrawCube(transform, material.Color);
				}
			}

			Renderer3D::EndScene();
		}
	}
}