#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace ath {

	class ATHENA_API Log {

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	public:

		static void Init();

		inline static std::shared_ptr<spdlog::logger> & GetCoreLogger() { return s_CoreLogger; };
		inline static std::shared_ptr<spdlog::logger> & GetClientLogger() { return s_ClientLogger; };
	};
}

#if 1
	// client side logging macros
	#define TRACE(...)               ::ath::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define INFO(...)                ::ath::Log::GetClientLogger()->info(__VA_ARGS__)
	#define WARN(...)                ::ath::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define ERROR(...)               ::ath::Log::GetClientLogger()->error(__VA_ARGS__)
	#define FATAL(...)               ::ath::Log::GetClientLogger()->fatal(__VA_ARGS__)

	// core logging macros
	#define CORE_TRACE(...)        ::ath::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define CORE_INFO(...)         ::ath::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define CORE_WARN(...)         ::ath::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define CORE_ERROR(...)        ::ath::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define CORE_FATAL(...)        ::ath::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#else

// create empty stub to compile project but not slow down solution

#define TRACE(...)
#define INFO(...)
#define WARN(...)
#define ERROR(...)
#define FATAL(...)

// core logging macros
#define CORE_TRACE(...)
#define CORE_INFO(...)
#define CORE_WARN(...)
#define CORE_ERROR(...)
#define CORE_FATAL(...)



#endif
