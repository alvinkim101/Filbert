#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

namespace Filbert
{
	struct NameComponent
	{
		std::string name;
	};

	struct TransformComponent
	{
		glm::vec3 translation{ 0.0f, 0.0f, 0.0f };
		glm::vec3 rotation{ 0.0f, 0.0f, 0.0f };
		glm::vec3 scale{ 1.0f, 1.0f, 1.0f };
	};

	struct ColorComponent
	{
		glm::vec4 color{ 1.0f, 0.0f, 0.0f, 1.0f };
	};
}
