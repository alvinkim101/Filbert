#pragma once

#include "Texture.h"

#include <glm/vec2.hpp>

namespace Filbert
{
	class TextureAtlas
	{
	public:
		TextureAtlas(const std::shared_ptr<Texture2D>& texture, const glm::vec2& regionSize) : m_texture(texture), m_regionSize(regionSize) {}

		const std::shared_ptr<Texture2D>& GetTexture() const { return m_texture; }
		const glm::vec2& GetRegionSize() const { return m_regionSize; }

	private:
		std::shared_ptr<Texture2D> m_texture;
		glm::vec2 m_regionSize; // Size in pixels. vec2 so that operations with it will result in a float
	};

	class SubTexture2D
	{
	public:
		SubTexture2D(const std::shared_ptr<TextureAtlas>& textureAtlas, const glm::uvec2& indices, const glm::uvec2& length = { 1, 1 } /* In case sub-texture spans multiple regions*/);
		SubTexture2D(const std::shared_ptr<Texture2D>& texture, const std::array<glm::vec2, 4>& textureCoordinates) : m_texture(texture), m_textureCoordinates(m_textureCoordinates) {}

		const std::array<glm::vec2, 4>& GetTextureCoordinates() const { return m_textureCoordinates; }
		const std::shared_ptr<Texture2D>& GetTexture() const { return m_texture; }

	private:
		std::shared_ptr<Texture2D> m_texture;
		std::array<glm::vec2, 4> m_textureCoordinates;
	};
}
