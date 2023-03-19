#pragma once

#include "entt.hpp"

#include "Components.h"
#include "Volum/Core/TimeStep.h"

namespace Volum
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		entt::entity CreateEntity();

		entt::registry& Reg() { return m_registry; }

		void OnUpdate(TimeStep ts);
	private:
		entt::registry m_registry;
	};
}