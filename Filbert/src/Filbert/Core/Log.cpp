#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Filbert
{
	std::shared_ptr<spdlog::logger> Log::s_coreLogger;
	std::shared_ptr<spdlog::logger> Log::s_clientLogger;

	Log::Log()
	{

	}

	Log::~Log()
	{

	}

	void Log::Init()
	{
		constexpr auto pattern = "%^[%T] %n: %v%$";
		constexpr auto level = spdlog::level::trace;

		spdlog::set_pattern(pattern);
		spdlog::set_level(level);

		s_coreLogger = spdlog::stdout_color_mt("FILBERT");
		s_clientLogger = spdlog::stdout_color_mt("CLIENT");
	}
}
