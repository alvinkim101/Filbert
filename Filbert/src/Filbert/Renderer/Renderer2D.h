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

		static void DrawQuad(const glm::vec3& translation /* Z used for depth */, const float rotation /* degrees */, const glm::vec2& scale, const glm::vec4& color, const std::shared_ptr<Texture2D>& texture);

		static void DrawQuad(const glm::vec2& translation, const float rotation, const glm::vec2& scale, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& translation, const float rotation, const glm::vec2& scale, const std::shared_ptr<Texture2D>& texture);
		static void DrawQuad(const glm::vec2& translation, const float rotation , const glm::vec2& scale, const glm::vec4& color, const std::shared_ptr<Texture2D>& texture);

		static void DrawQuad(const glm::vec3& translation, const float rotation, const glm::vec2& scale, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& translation, const float rotation, const glm::vec2& scale, const std::shared_ptr<Texture2D>& texture);

		struct Stats
		{
			unsigned int drawCalls = 0;
			unsigned int quadCount = 0;
		};

		static Stats GetStats();
		static void ResetStats();

	private:
		static void Flush();
	};
}
