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

		switch (m_channels)
		{
		case 4:
			m_internalFormat = GL_RGBA8;
			m_dataFormat = GL_RGBA;
			break;

		case 3:
			m_internalFormat = GL_RGB8;
			m_dataFormat = GL_RGB;
			break;

		default:
			FB_CORE_ASSERT(false, "Number of channels not supported");
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &m_texture);

		glTextureParameteri(m_texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureStorage2D(m_texture, 1, m_internalFormat, m_width, m_height);
		glTextureSubImage2D(m_texture, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::OpenGLTexture2D(int width, int height)
	{
		m_width = width;
		m_height = height;
		m_internalFormat = GL_RGBA8;
		m_dataFormat = GL_RGBA;
		m_channels = 4;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_texture);

		glTextureParameteri(m_texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureStorage2D(m_texture, 1, m_internalFormat, m_width, m_height);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_texture);
	}

	void OpenGLTexture2D::SetData(void* data, std::size_t size)
	{
		FB_CORE_ASSERT(size == m_width * m_height * m_channels, "Data size not valid");
		glTextureSubImage2D(m_texture, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::Bind(unsigned int unit) const
	{
		glBindTextureUnit(unit, m_texture);
	}
}
