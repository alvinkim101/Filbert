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

		// Rotation in degrees
		static void DrawQuad(const glm::vec2& translation, const float rotation, const glm::vec2& scale, const glm::vec3& color);
		static void DrawQuad(const glm::vec3& translation, const float rotation, const glm::vec2& scale, const glm::vec3& color); // Explicitly render objects in front / behind others
	};
}
