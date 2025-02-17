#pragma once

#include "Camera.h"
#include "Texture.h"
#include "SubTexture.h"

namespace Filbert
{
	class Renderer2D
	{
	public:
		static void Initialize();
		static void Deinitialize();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		// TODO: Make rotation optional
		static void DrawQuad(const glm::vec3& translation /* Z used for depth */, const float rotation /* degrees */, const glm::vec2& scale, const glm::vec4& color, const std::shared_ptr<Texture2D> texture, const std::array<glm::vec2, 4>& textureCoordinates);

		static inline void DrawQuad(const glm::vec2& translation, const float rotation, const glm::vec2& scale, const glm::vec4& color)
		{
			DrawQuad(glm::vec3(translation, 0.0f), rotation, scale, color, s_whiteTexture);
		}

		static inline void DrawQuad(const glm::vec2& translation, const float rotation, const glm::vec2& scale, const std::shared_ptr<Texture2D>& texture)
		{
			DrawQuad(glm::vec3(translation, 0.0f), rotation, scale, s_whiteColor, texture);
		}

		static inline void DrawQuad(const glm::vec2& translation, const float rotation, const glm::vec2& scale, const std::shared_ptr<SubTexture2D>& subTexture)
		{
			DrawQuad(glm::vec3(translation, 0.0f), rotation, scale, s_whiteColor, subTexture);
		}

		static inline void DrawQuad(const glm::vec2& translation, const float rotation, const glm::vec2& scale, const glm::vec4& color, const std::shared_ptr<Texture2D>& texture)
		{
			DrawQuad(glm::vec3(translation, 0.0f), rotation, scale, color, texture);
		}

		static inline void DrawQuad(const glm::vec2& translation, const float rotation, const glm::vec2& scale, const glm::vec4& color, const std::shared_ptr<SubTexture2D>& subTexture)
		{
			DrawQuad(glm::vec3(translation, 0.0f), rotation, scale, color, subTexture);
		}

		static inline void DrawQuad(const glm::vec3& translation, const float rotation, const glm::vec2& scale, const glm::vec4& color)
		{
			DrawQuad(translation, rotation, scale, color, s_whiteTexture);
		}

		static inline void DrawQuad(const glm::vec3& translation, const float rotation, const glm::vec2& scale, const std::shared_ptr<Texture2D>& texture)
		{
			DrawQuad(translation, rotation, scale, s_whiteColor, texture);
		}

		static inline void DrawQuad(const glm::vec3& translation, const float rotation, const glm::vec2& scale, const std::shared_ptr<SubTexture2D>& subTexture)
		{
			DrawQuad(translation, rotation, scale, s_whiteColor, subTexture);
		}

		static inline void DrawQuad(const glm::vec3& translation, const float rotation, const glm::vec2& scale, const glm::vec4& color, const std::shared_ptr<Texture2D>& texture)
		{
			DrawQuad(translation, rotation, scale, color, texture, s_defaultTextureCoordinates);
		}

		static inline void DrawQuad(const glm::vec3& translation, const float rotation, const glm::vec2& scale, const glm::vec4& color, const std::shared_ptr<SubTexture2D>& subTexture)
		{
			FB_CORE_ASSERT(subTexture, "Null sub-texture");
			DrawQuad(translation, rotation, scale, color, subTexture->GetTexture(), subTexture->GetTextureCoordinates());
		}

		struct Stats
		{
			unsigned int drawCalls = 0;
			unsigned int quadCount = 0;
		};

		static Stats GetStats();
		static void ResetStats();

	private:
		static void Flush();

		static std::shared_ptr<Texture2D> s_whiteTexture;
		static const glm::vec4 s_whiteColor;
		static const std::array<glm::vec2, 4> s_defaultTextureCoordinates;
	};
}
