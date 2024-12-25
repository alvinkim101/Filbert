#pragma once

#include "Core.h"
#include "Filbert/Events/Event.h"
#include "pch.h"

namespace Filbert
{
	struct WindowProps
	{
		std::string title;
		unsigned int width, height;

		WindowProps(const std::string& title = "Filbert Engine", unsigned int width = 1920, unsigned int height = 1080)
			: title(title), width(width), height(height) {}
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = 0 {};

		virtual void ProcessInput() = 0;
		virtual void Clear() = 0;
		virtual void SwapBuffers() = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;

		virtual bool IsVSyncEnabled() const = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Seconds
		virtual float GetTime() const = 0; // Will float precision be an issue?

		virtual void* GetNativeWindow() = 0;

		static std::unique_ptr<Window> Create(const WindowProps& props = WindowProps());
	};
}
