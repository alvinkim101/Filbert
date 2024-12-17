#pragma once

namespace Filbert
{
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;

		virtual void Bind(unsigned int unit) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		void Bind(unsigned int unit = 0) const = 0;

		static Texture2D* Create(const std::string& fileName);
	};
}
