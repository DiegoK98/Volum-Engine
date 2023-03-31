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
			auto& tagComp = entity.GetComponent<TagComponent>();

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tagComp.Tag.c_str());
			if (ImGui::InputText("Tag", buffer, 256))
			{
				tagComp.Tag = std::string(buffer);
			}

			ImGui::Separator();
		}

		if (entity.HasComponent<TransformComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform Component"))
			{
				auto& transformComp = entity.GetComponent<TransformComponent>();

				ImGui::DragFloat3("Position", glm::value_ptr(transformComp.Transform[3]), 0.1f);

				ImGui::TreePop();
			}

			ImGui::Separator();
		}
		if (entity.HasComponent<CameraComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(CameraComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Camera Component"))
			{
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
