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
		static std::shared_ptr<Texture2D> Create(const std::string& fileName);
	};
}
