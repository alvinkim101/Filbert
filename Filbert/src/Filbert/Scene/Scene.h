#pragma once

#include <entt/entt.hpp>

namespace Filbert
{
	//https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system/465d90e0f5961adc460cd9d1e9358370987fbcd3

	class Scene
	{
		friend class Entity;

	public:
		Scene();
		~Scene();

		void Update(float deltaTime);
		void Render();

	private:
		entt::registry m_registry;
	};
}
