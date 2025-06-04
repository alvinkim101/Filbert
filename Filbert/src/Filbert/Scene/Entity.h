#pragma once

#include <entt/entt.hpp>

#include "Scene.h"

namespace Filbert
{
	class Entity
	{
		friend class Scene;

	public:
		Entity(std::weak_ptr<Scene> scene);

		void Create();
		void Destroy();

		template <typename T>
		bool HasComponent() const;

		// true if entity has all the given components
		template <typename... T>
		bool HasAllComponents() const;

		// true if entity has at least one of the given components
		template <typename... T>
		bool HasAnyComponents() const;

		template <typename T>
		T GetComponent() const;

		template <typename T, typename... Args>
		void AddComponent(Args&&... args);

		template <typename T>
		void RemoveComponent();

	private:
		entt::entity m_entity{ entt::null };
		std::weak_ptr<Scene> m_scene;
	};

	template<typename T>
	bool Entity::HasComponent() const
	{
		return HasAllComponents<T>();
	}

	template <typename... T>
	bool Entity::HasAllComponents() const
	{
		FB_CORE_ASSERT(m_entity != entt::null, "Null entity");

		if (auto scene = m_scene.lock())
		{
			return scene->m_registry.all_of<T...>(m_entity);
		}
		else
		{
			return false;
		}
	}

	template <typename... T>
	bool Entity::HasAnyComponents() const
	{
		FB_CORE_ASSERT(m_entity != entt::null, "Null entity");

		if (auto scene = m_scene.lock())
		{
			return scene->m_registry.any_of<T...>(m_entity);
		}
		else
		{
			return false;
		}
	}

	template <typename T>
	T Entity::GetComponent() const
	{
		FB_CORE_ASSERT(m_entity != entt::null, "Null entity");
		FB_CORE_ASSERT(HasComponent<T>());

		if (auto scene = m_scene.lock())
		{
			return scene->m_registry.get<T>(m_entity);
		}
	}

	template<typename T, typename... Args>
	inline void Entity::AddComponent(Args&&... args)
	{
		FB_CORE_ASSERT(m_entity != entt::null, "Null entity");

		if (auto scene = m_scene.lock())
		{
			scene->m_registry.emplace<T>(m_entity, std::forward<Args>(args)...);
		}
	}

	template <typename T>
	void Entity::RemoveComponent()
	{
		FB_CORE_ASSERT(m_entity != entt::null, "Null entity");
		FB_CORE_ASSERT(HasComponent<T>());

		if (auto scene = m_scene.lock())
		{
			scene->m_registry.erase<T>(m_entity); // Could also remove the component assert and use remove instead
		}
	}
}
