#pragma once

#include "entt.hpp"

#include "Volum/Core/TimeStep.h"

namespace Volum
{
	// Forw decl
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());

		void OnUpdate(TimeStep ts);
		void OnViewportResize(uint32_t width, uint32_t height);

		bool m_viewportFocused = false;
		bool m_viewportHovered = false;
	private:
		entt::registry m_registry;

		uint32_t m_viewportWidth = 0, m_viewportHeight = 0;

		friend class Entity;
		friend class SceneHierarchyPanel;
	};
}
