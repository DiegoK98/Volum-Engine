#pragma once

#include "entt.hpp"

#include "Components.h"
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
	private:
		entt::registry m_registry;

		friend class Entity;
	};
}