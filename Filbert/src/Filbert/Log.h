#pragma once

#include "Core.h"

#include <spdlog/spdlog.h>

namespace Filbert
{
	class Log
	{
	public:
		Log();
		~Log();

		static void Init();

		static std::shared_ptr<spdlog::logger> GetCoreLogger() { return s_coreLogger; };
		static std::shared_ptr<spdlog::logger> GetClientLogger() { return s_clientLogger; };

	private:
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;
	};
}

// Core log macros
#define FB_CORE_TRACE(...) ::Filbert::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FB_CORE_DEBUG(...) ::Filbert::Log::GetCoreLogger()->debug(__VA_ARGS__)
#define FB_CORE_INFO(...) ::Filbert::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FB_CORE_WARN(...) ::Filbert::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FB_CORE_ERROR(...) ::Filbert::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FB_CORE_CRITICAL(...) ::Filbert::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define FB_TRACE(...) ::Filbert::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FB_DEBUG(...) ::Filbert::Log::GetClientLogger()->debug(__VA_ARGS__)
#define FB_INFO(...) ::Filbert::Log::GetClientLogger()->info(__VA_ARGS__)
#define FB_WARN(...) ::Filbert::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FB_ERROR(...) ::Filbert::Log::GetClientLogger()->error(__VA_ARGS__)
#define FB_CRITICAL(...) ::Filbert::Log::GetClientLogger()->critical(__VA_ARGS__)
