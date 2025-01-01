#pragma once

#include "Camera.h"

namespace Filbert
{
	class Renderer2D
	{
	public:
		static void Initialize();
		static void Deinitialize();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec3& color); // Explicitly render objects in front / behind others
	};
}
