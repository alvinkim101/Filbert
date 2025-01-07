#pragma once

// Trace Event Format https://docs.google.com/document/d/1CvAClvFfyA5R-PhYUmn5OOQtYMH4h6I0nSsKchNAySU

namespace Filbert
{
	class Profiler
	{
	public:
		struct CompleteEvent
		{
			std::string name;
			long long start;
			long long duration;
			DWORD processID; // pid_t on Unix
			std::thread::id threadID;
			std::unordered_map<std::string, std::string> arguments;
		};

		class Stopwatch
		{
		public:
			Stopwatch(std::string_view name);
			~Stopwatch();

		private:
			std::string m_name;
			std::chrono::steady_clock::time_point m_start{ std::chrono::steady_clock::now() };
		};

		static void Begin(std::string_view fileName);
		static void Write(const CompleteEvent& event);
		static void End();

	private:
		static std::ofstream s_out;
	};
}

#ifdef FB_ASSERTS_ENABLED
	#define FB_PROFILE_FN() FB_PROFILE_INTERMEDIARY_1(__FUNCSIG__)

	// To let __LINE__ macro expand correctly
	#define FB_PROFILE_INTERMEDIARY_1(name) FB_PROFILE_INTERMEDIARY_2(name, __LINE__)
	#define FB_PROFILE_INTERMEDIARY_2(name, line) FB_PROFILE(name, line)

	// Concatenate line number so that multiple stopwatches can be made in the same scope
	#define FB_PROFILE(name, line) ::Filbert::Profiler::Stopwatch stopwatch##line(name)
#else
	#define FB_PROFILE_FN()
#endif
