#pragma once

#include "Camera.h"
#include "Texture.h"

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
		static void DrawQuad(const glm::vec2& translation, const float rotation, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, unsigned int textureSlot = 0);

		// Explicitly render objects in front / behind others
		static void DrawQuad(const glm::vec3& translation, const float rotation, const glm::vec2& scale, const glm::vec3& color);
		static void DrawQuad(const glm::vec3& translation, const float rotation, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, unsigned int textureSlot = 0);
	};
}
