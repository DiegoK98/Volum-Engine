#pragma once

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>

#include <thread>

namespace Volum {
	struct ProfileResult
	{
		std::string Name;
		long long Start, End;
		uint32_t ThreadID;
	};

	struct InstrumentationSession
	{
		std::string Name;
	};

	class Instrumentor
	{
	private:
		InstrumentationSession* m_currentSession;
		std::ofstream m_outputStream;
		int m_profileCount;
	public:
		Instrumentor()
			: m_currentSession(nullptr), m_profileCount(0)
		{
		}

		void BeginSession(const std::string& name, const std::string& filepath = "results.json")
		{
			m_outputStream.open(filepath);
			WriteHeader();
			m_currentSession = new InstrumentationSession{ name };
		}

		void EndSession()
		{
			WriteFooter();
			m_outputStream.close();
			delete m_currentSession;
			m_currentSession = nullptr;
			m_profileCount = 0;
		}

		void WriteProfile(const ProfileResult& result)
		{
			if (m_profileCount++ > 0)
				m_outputStream << ",";

			std::string name = result.Name;
			std::replace(name.begin(), name.end(), '"', '\'');

			m_outputStream << "{";
			m_outputStream << "\"cat\":\"function\",";
			m_outputStream << "\"dur\":" << (result.End - result.Start) << ',';
			m_outputStream << "\"name\":\"" << name << "\",";
			m_outputStream << "\"ph\":\"X\",";
			m_outputStream << "\"pid\":0,";
			m_outputStream << "\"tid\":" << result.ThreadID << ",";
			m_outputStream << "\"ts\":" << result.Start;
			m_outputStream << "}";

			m_outputStream.flush();
		}

		void WriteHeader()
		{
			m_outputStream << "{\"otherData\": {},\"traceEvents\":[";
			m_outputStream.flush();
		}

		void WriteFooter()
		{
			m_outputStream << "]}";
			m_outputStream.flush();
		}

		static Instrumentor& Get()
		{
			static Instrumentor instance;
			return instance;
		}
	};

	class InstrumentationTimer
	{
	public:
		InstrumentationTimer(const char* name)
			: m_name(name), m_stopped(false)
		{
			m_startTimepoint = std::chrono::high_resolution_clock::now();
		}

		~InstrumentationTimer()
		{
			if (!m_stopped)
				Stop();
		}

		void Stop()
		{
			auto endTimepoint = std::chrono::high_resolution_clock::now();

			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimepoint).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

			uint32_t threadID = (uint32_t)std::hash<std::thread::id>{}(std::this_thread::get_id());
			Instrumentor::Get().WriteProfile({ m_name, start, end, threadID });

			m_stopped = true;
		}
	private:
		const char* m_name;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimepoint;
		bool m_stopped;
	};
}

#define VLM_PROFILER 1
#define VLM_RENDERER_PROFILER 1

#if VLM_PROFILER or VLM_RENDERER_PROFILER
	// Resolve which function signature macro will be used. Note that this only is resolved when the
	// (pre)compiler starts, so the syntax highlighting could mark the wrong one in your editor!
	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define VLM_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define VLM_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__FUNCSIG__)
		#define VLM_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define VLM_FUNC_SIG __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
		#define VLM_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define VLM_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define VLM_FUNC_SIG __func__
	#else
		#define VLM_FUNC_SIG "VLM_FUNC_SIG unknown!"
	#endif
#endif

#if VLM_PROFILER
	#define VLM_PROFILE_BEGIN_SESSION(name, filepath) ::Volum::Instrumentor::Get().BeginSession(name, filepath)
	#define VLM_PROFILE_END_SESSION() ::Volum::Instrumentor::Get().EndSession()
	#define VLM_PROFILE_SCOPE(name) ::Volum::InstrumentationTimer timer##__LINE__(name);
	#define VLM_PROFILE_FUNCTION() VLM_PROFILE_SCOPE(VLM_FUNC_SIG)
#else
	#define VLM_PROFILE_BEGIN_SESSION(name, filepath)
	#define VLM_PROFILE_END_SESSION()
	#define VLM_PROFILE_SCOPE(name)
	#define VLM_PROFILE_FUNCTION()
#endif

#if VLM_RENDERER_PROFILER
	#define VLM_RENDERER_PROFILE_BEGIN_SESSION(name, filepath) ::Volum::Instrumentor::Get().BeginSession(name, filepath)
	#define VLM_RENDERER_PROFILE_END_SESSION() ::Volum::Instrumentor::Get().EndSession()
	#define VLM_RENDERER_PROFILE_SCOPE(name) ::Volum::InstrumentationTimer timer##__LINE__(name);
	#define VLM_RENDERER_PROFILE_FUNCTION() VLM_RENDERER_PROFILE_SCOPE(VLM_FUNC_SIG)
#else
	#define VLM_RENDERER_PROFILE_BEGIN_SESSION(name, filepath)
	#define VLM_RENDERER_PROFILE_END_SESSION()
	#define VLM_RENDERER_PROFILE_SCOPE(name)
	#define VLM_RENDERER_PROFILE_FUNCTION()
#endif
