#include "SceneHierarchyPanel.h"

#include <ImGui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

namespace Volum
{
	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene> context)
	{
		SetContext(context);
	}

	void SceneHierarchyPanel::SetContext(const Ref<Scene> context)
	{
		m_context = context;
	}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");
		m_context->m_registry.each([&](auto entityID)
			{
				Entity entity { entityID , m_context.get()};
				DrawEntityNode(entity);
			});

		if (ImGui::IsWindowHovered() && ImGui::IsMouseDown(0))
		{
			m_selecionContext = {};
		}

		ImGui::End();

		ImGui::Begin("Properties");
		
		if (m_selecionContext)
		{
			DrawComponents(m_selecionContext);
		}

		ImGui::End();
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto& tagComp = entity.GetComponent<TagComponent>();

		ImGuiTreeNodeFlags flags = ((m_selecionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tagComp.Tag.c_str());

		if (ImGui::IsItemClicked())
		{
			m_selecionContext = entity;
		}

		if (opened)
		{
			ImGui::TreePop();
		}
	}

	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().Tag;

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tag.c_str());
			if (ImGui::InputText("Tag", buffer, 256))
			{
				tag = std::string(buffer);
			}

			ImGui::Separator();
		}

		if (entity.HasComponent<TransformComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform Component"))
			{
				auto& transform = entity.GetComponent<TransformComponent>().Transform;

				ImGui::DragFloat3("Position", glm::value_ptr(transform[3]), 0.1f);

				ImGui::TreePop();
			}

			ImGui::Separator();
		}
		if (entity.HasComponent<CameraComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(CameraComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Camera Component"))
			{
				auto& cameraComp = entity.GetComponent<CameraComponent>();
				auto& camera = cameraComp.Camera;

				const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };
				const char* currentProjectionTypeString = projectionTypeStrings[(int)camera.GetProjectionType()];
				if (ImGui::BeginCombo("Projection type", currentProjectionTypeString))
				{
					for (int i = 0; i < 2; i++)
					{
						bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];

						if (ImGui::Selectable(projectionTypeStrings[i], isSelected))
						{
							currentProjectionTypeString = projectionTypeStrings[i];
							camera.SetProjectionType((SceneCamera::ProjectionType)i);
						}

						if (isSelected)
							ImGui::SetItemDefaultFocus();
					}

					ImGui::EndCombo();
				}

				if (camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective)
				{
					float persFovY = camera.GetPerspectiveFovY();
					if (ImGui::DragFloat("Fov Y", &persFovY))
						camera.SetPerspectiveFovY(persFovY);

					float persNear = camera.GetPerspectiveNear();
					if (ImGui::DragFloat("Near Clip", &persNear))
						camera.SetPerspectiveNear(persNear);

					float persFar = camera.GetPerspectiveFar();
					if (ImGui::DragFloat("Far Clip", &persFar))
						camera.SetPerspectiveFar(persFar);
				}
				else
				{
					float orthoSize = camera.GetOrthographicSize();
					if (ImGui::DragFloat("Size", &orthoSize))
						camera.SetOrthographicSize(orthoSize);

					float orthoNear = camera.GetOrthographicNear();
					if (ImGui::DragFloat("Near Clip", &orthoNear))
						camera.SetOrthographicNear(orthoNear);

					float orthoFar = camera.GetOrthographicFar();
					if (ImGui::DragFloat("Far Clip", &orthoFar))
						camera.SetOrthographicFar(orthoFar);
				}

				ImGui::TreePop();
			}

			ImGui::Separator();
		}
		if (entity.HasComponent<NativeScriptComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(NativeScriptComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Native Script Component"))
			{
				ImGui::TreePop();
			}

			ImGui::Separator();
		}
		if (entity.HasComponent<SpriteRendererComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(SpriteRendererComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Sprite Renderer Component"))
			{
				ImGui::TreePop();
			}

			ImGui::Separator();
		}
		if (entity.HasComponent<MeshComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(MeshComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Mesh Component"))
			{
				ImGui::TreePop();
			}

			ImGui::Separator();
		}
		if (entity.HasComponent<MaterialComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(MaterialComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Material Component"))
			{
				ImGui::TreePop();
			}

			ImGui::Separator();
		}
	}
}
