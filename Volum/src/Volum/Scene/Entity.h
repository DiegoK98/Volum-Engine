#pragma once

#include "Scene.h"
#include "entt.hpp"

namespace Volum
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity entity, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			VLM_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");

			return m_entityHandle.emplace<T>(std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			VLM_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");

			return m_entityHandle.get<T>();
		}

		template<typename T>
		bool HasComponent()
		{
			return m_entityHandle.any_of<T>();
		}

		template<typename T>
		bool RemoveComponent()
		{
			VLM_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");

			return m_entityHandle.remove<T>();
		}

		operator bool() const { return m_entityHandle ? true : false; }
		operator uint32_t() const { return (uint32_t)m_entityHandle.entity(); }

		bool operator==(const Entity& other) const
		{
			return m_entityHandle == other.m_entityHandle;
		}

		bool operator!=(const Entity& other) const
		{
			return m_entityHandle != other.m_entityHandle;
		}

	private:
		entt::handle m_entityHandle;
	};
}
