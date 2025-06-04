#include "Entity.h"

#include "Components.h"

namespace Filbert
{
	Entity::Entity(std::weak_ptr<Scene> scene) : m_scene(scene)
	{
		Create();
	}

	void Entity::Create()
	{
		FB_CORE_ASSERT(m_entity == entt::null, "Non-null entity");

		if (auto scene = m_scene.lock())
		{
			m_entity = scene->m_registry.create();

			// Default components
			AddComponent<NameComponent>();
			AddComponent<TransformComponent>();
		}
	}

	void Entity::Destroy()
	{
		FB_CORE_ASSERT(m_entity != entt::null, "Null entity");

		if (auto scene = m_scene.lock())
		{
			scene->m_registry.destroy(m_entity);
			m_entity = entt::null;
		}
	}
}
