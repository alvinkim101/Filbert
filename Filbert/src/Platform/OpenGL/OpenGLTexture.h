#pragma once

#include "Filbert/Renderer/Texture.h"

namespace Filbert
{
	// TODO: Replace hardcoded parameters
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& fileName);
		OpenGLTexture2D(int width, int height);
		~OpenGLTexture2D();

		int GetWidth() const override { return m_width; }
		int GetHeight() const override { return m_height; }

		void Bind(unsigned int unit = 0) const override;

		void SetData(void* data, std::size_t size) override;

	private:
		std::string m_fileName;

		unsigned int m_texture = 0;

		int m_width = 0;
		int m_height = 0;
		int m_channels = 0;
		int m_internalFormat = 0;
		int m_dataFormat = 0;
	};
}
