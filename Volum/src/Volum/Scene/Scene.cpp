#include "vlmpch.h"

#include "Scene.h"

#include "Components.h"
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
		// Update scripts
		{
			m_registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
			{
				// TODO: Move to Scene::OnScenePlay (Also, call OnDestroy in Scene::OnSceneStop)
				if (!nsc.Instance)
				{
					nsc.Instance = nsc.InstantiateScript();
					nsc.Instance->m_entity = Entity{ entity, this };
					nsc.Instance->OnCreate();
				}

				nsc.Instance->OnUpdate(ts);
			});
		}

		Camera* mainCamera = nullptr;
		glm::mat4* cameraTransform = nullptr;
		{
			auto view = m_registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

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

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_viewportWidth = width;
		m_viewportHeight = height;

		// Resize our non-fixedAspectRatio cameras
		auto view = m_registry.view<TransformComponent, CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);

			if (!cameraComponent.FixedAspectRatio)
				cameraComponent.Camera.SetViewportSize(width, height);
		}
	}
}