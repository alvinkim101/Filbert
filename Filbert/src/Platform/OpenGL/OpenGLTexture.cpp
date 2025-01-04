#include "OpenGLTexture.h"

#include <stb_image.h>

#include <glad/gl.h>

namespace Filbert
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& fileName) : m_fileName(fileName)
	{
		FB_CORE_ASSERT(std::filesystem::exists(fileName), "File does not exist");
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(fileName.c_str(), &m_width, &m_height, &m_channels, 0);
		FB_CORE_ASSERT(data, "Failed to load image");

		GLenum internalFormat, format;
		switch (m_channels)
		{
		case 4:
			internalFormat = GL_RGBA8;
			format = GL_RGBA;
			break;

		case 3:
			internalFormat = GL_RGB8;
			format = GL_RGB;
			break;

		default:
			FB_CORE_ASSERT(false, "Number of channels not supported");
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &m_texture);

		glTextureParameteri(m_texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureStorage2D(m_texture, 1, internalFormat, m_width, m_height);
		glTextureSubImage2D(m_texture, 0, 0, 0, m_width, m_height, format, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_texture);
	}

	void OpenGLTexture2D::Bind(unsigned int unit) const
	{
		glBindTextureUnit(unit, m_texture);
	}
}
