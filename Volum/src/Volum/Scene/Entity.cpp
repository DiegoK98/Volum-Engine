#include "vlmpch.h"

#include "Entity.h"

namespace Volum
{
	Entity::Entity(entt::entity entity, Scene* scene)
		: m_entityHandle(entt::handle(scene->m_registry, entity))
	{

	}
}