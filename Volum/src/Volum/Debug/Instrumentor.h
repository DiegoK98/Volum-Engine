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
		std::thread::id ThreadID;
	};

	struct InstrumentationSession
	{
		std::string Name;
	};

	class Instrumentor
	{
	private:
		std::mutex m_Mutex;
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
			std::lock_guard lock(m_Mutex);
			if (m_currentSession) {
				// If there is already a current session, then close it before beginning new one.
				// Subsequent profiling output meant for the original session will end up in the
				// newly opened session instead. That's better than having badly formatted profiling output.
				if (Log::GetCoreLogger()) { // Edge case: BeginSession() might be before Log::Init()
					VLM_CORE_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open.", name, m_currentSession->Name);
				}
				InternalEndSession();
			}
			m_outputStream.open(filepath);
			if (m_outputStream.is_open()) {
				m_currentSession = new InstrumentationSession({ name });
				WriteHeader();
			}
			else {
				if (Log::GetCoreLogger()) { // Edge case: BeginSession() might be before Log::Init()
					VLM_CORE_ERROR("Instrumentor could not open results file '{0}'.", filepath);
				}
			}
		}

		void EndSession()
		{
			std::lock_guard lock(m_Mutex);
			InternalEndSession();
		}

		void WriteProfile(const ProfileResult& result)
		{
			std::stringstream json;

			if (m_profileCount++ > 0)
				json << ",";

			std::string name = result.Name;
			std::replace(name.begin(), name.end(), '"', '\'');

			json << "{";
			json << "\"cat\":\"function\",";
			json << "\"dur\":" << (result.End - result.Start) << ',';
			json << "\"name\":\"" << name << "\",";
			json << "\"ph\":\"X\",";
			json << "\"pid\":0,";
			json << "\"tid\":" << result.ThreadID << ",";
			json << "\"ts\":" << result.Start;
			json << "}";

			std::lock_guard lock(m_Mutex);
			if (m_currentSession) {
				m_outputStream << json.str();
				m_outputStream.flush();
			}
		}

		static Instrumentor& Get()
		{
			static Instrumentor instance;
			return instance;
		}

	private:
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

		// Note: you must already own lock on m_Mutex before
		// calling InternalEndSession()
		void InternalEndSession()
		{
			if (m_currentSession)
			{
				WriteFooter();
				m_outputStream.close();
				delete m_currentSession;
				m_currentSession = nullptr;
				m_profileCount = 0;
			}
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

			Instrumentor::Get().WriteProfile({ m_name, start, end, std::this_thread::get_id() });

			m_stopped = true;
		}
	private:
		const char* m_name;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimepoint;
		bool m_stopped;
	};
}

#define VLM_PROFILER 0
#define VLM_RENDERER_PROFILER 0

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
