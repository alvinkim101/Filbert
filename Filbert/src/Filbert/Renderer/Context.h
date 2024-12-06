#pragma once

namespace Filbert
{
	class Context
	{
	public:
		virtual ~Context() {};
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		static Context* Create(void* window);
	};
}
