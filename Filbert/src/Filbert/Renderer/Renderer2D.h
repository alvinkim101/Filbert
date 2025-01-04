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

		inline static void DrawQuad(const glm::vec2& translation, const float rotation, const glm::vec2& scale, const glm::vec3& color);
		inline static void DrawQuad(const glm::vec2& translation, const float rotation, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, unsigned int textureSlot = 0);
		inline static void DrawQuad(const glm::vec2& translation, const float rotation , const glm::vec2& scale, const glm::vec3& color, const std::shared_ptr<Texture>& texture, unsigned int textureSlot = 0);

		// Explicitly render objects in front / behind others
		inline static void DrawQuad(const glm::vec3& translation, const float rotation, const glm::vec2& scale, const glm::vec3& color);
		inline static void DrawQuad(const glm::vec3& translation, const float rotation, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, unsigned int textureSlot = 0);

		static void DrawQuad(const glm::vec3& translation, const float rotation /* degrees */, const glm::vec2& scale, const glm::vec3& color, const std::shared_ptr<Texture>& texture, unsigned int textureSlot = 0);
	};
}
