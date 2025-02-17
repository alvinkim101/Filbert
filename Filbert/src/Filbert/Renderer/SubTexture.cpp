#include "SubTexture.h"

namespace Filbert
{
	SubTexture2D::SubTexture2D(const std::shared_ptr<TextureAtlas>& textureAtlas, const glm::uvec2& indices, const glm::uvec2& length)
		: m_texture(textureAtlas->GetTexture())
	{
		auto [width, height] = m_texture->GetDimensions();
		glm::vec2 regionSize = textureAtlas->GetRegionSize();

		// Counter clockwise starting from bottom left. Dividing by width/height so that coordinates are between 0 and 1.
		m_textureCoordinates[0] = { (indices.x * regionSize.x) / width, (indices.y * regionSize.y) / height };
		m_textureCoordinates[1] = { ((indices.x + length.x) * regionSize.x) / width, (indices.y * regionSize.y) / height };
		m_textureCoordinates[2] = { ((indices.x + length.x) * regionSize.x) / width, ((indices.y + length.y) * regionSize.y) / height };
		m_textureCoordinates[3] = { (indices.x * regionSize.x) / width, ((indices.y + length.y) * regionSize.y) / height };
	}
}
