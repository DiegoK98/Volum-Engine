#pragma once

#include "Entity.h"

namespace Volum
{
	class ScriptableEntity
	{
	public:
		virtual ~ScriptableEntity() {}

		template<typename T>
		T& GetComponent()
		{
			return m_entity.GetComponent<T>();
		}

	protected:
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate(TimeStep ts) {}
	private:
		Entity m_entity;

		friend class Scene;
	};
}