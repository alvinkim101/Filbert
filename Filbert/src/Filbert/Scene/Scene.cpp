#include "Scene.h"

#include "Components.h"
#include "Filbert/Renderer/Renderer2D.h"

namespace Filbert
{
	Scene::Scene()
	{

	}

	Scene::~Scene()
	{

	}

	void Scene::Update(float deltaTime)
	{
		
	}

	void Scene::Render()
	{
		// To-do: Understand differences between view and group

		auto view = m_registry.view<TransformComponent, NameComponent, ColorComponent>();

		for (auto entity : view)
		{
			/*
			// a component at a time ...
			auto& position = view.get<position>(entity);
			auto& velocity = view.get<velocity>(entity);

			// ... multiple components ...
			auto [pos, vel] = view.get<position, velocity>(entity);

			// ... all components at once
			auto [pos, vel, rend] = view.get(entity);
			*/

			auto [transform, name, color] = view.get(entity);
			Renderer2D::DrawQuad(transform.translation, transform.rotation.z, transform.scale, color.color);
		}
	}
}
