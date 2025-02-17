#pragma once

namespace Filbert
{
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
		std::pair<int, int> GetDimensions() const { return { GetWidth(), GetHeight() }; }

		virtual void Bind(unsigned int unit) const = 0;

		virtual void SetData(void* data, std::size_t size) = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static std::shared_ptr<Texture2D> Create(const std::string& fileName);
		static std::shared_ptr<Texture2D> Create(int width, int height);
	};
}
