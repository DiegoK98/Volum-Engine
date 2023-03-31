#pragma once

#include <Volum.h>

namespace Volum
{
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene> context);

		void SetContext(const Ref<Scene> context);

		void OnImGuiRender();
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);

		Ref<Scene> m_context;
		Entity m_selecionContext;
	};
}
