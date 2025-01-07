#include "Profiler.h"

#include <nlohmann/json.hpp>

#ifdef FB_PLATFORM_WINDOWS
#include <processthreadsapi.h>
#else
#include <unistd.h>
#endif

namespace Filbert
{
	std::ofstream Profiler::s_out;

	void Profiler::Begin(std::string_view fileName)
	{
		FB_CORE_ASSERT(!s_out.is_open(), "Profiler already started");

		s_out.open(fileName);
		s_out << "[\n";
	}

	void Profiler::Write(const CompleteEvent& event)
	{
		FB_CORE_ASSERT(s_out.is_open(), "Profiler has not started");

		nlohmann::json json;
		json["name"] = event.name;
		json["ph"] = "X";
		json["ts"] = event.start;
		json["dur"] = event.duration;
		json["pid"] = event.processID;
		json["tid"] = std::hash<std::thread::id>()(event.threadID);
		for (const auto& [key, value] : event.arguments)
		{
			json["args"][key] = value;
		}

		s_out << "\t" << json << ",\n";
		s_out.flush();
	}

	void Profiler::End()
	{
		FB_CORE_ASSERT(s_out.is_open(), "Profiler has not started");

		s_out << "\t{}\n]\n"; // Empty object to handle trailing comma
		s_out.close();
	}

	Profiler::Stopwatch::Stopwatch(std::string_view name) : m_name(name)
	{

	}

	Profiler::Stopwatch::~Stopwatch()
	{
		std::chrono::steady_clock::time_point end{ std::chrono::steady_clock::now() };
		std::chrono::duration duration = end - m_start;

		CompleteEvent event
		{
			m_name,
			std::chrono::duration_cast<std::chrono::microseconds>(m_start.time_since_epoch()).count(),
			std::chrono::duration_cast<std::chrono::microseconds>(duration).count(),
			#ifdef FB_PLATFORM_WINDOWS
			GetCurrentProcessId(),
			#else
			getpid(),
			#endif
			std::this_thread::get_id()
		};

		Profiler::Write(event);
	}
}
