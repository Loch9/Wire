#pragma once

#include "Wire/Core/Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Wire {

	class Log
	{
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};

}

#define WR_CORE_TRACE(...)    ::Wire::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define WR_CORE_INFO(...)     ::Wire::Log::GetCoreLogger()->info(__VA_ARGS__)
#define WR_CORE_WARN(...)     ::Wire::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define WR_CORE_ERROR(...)    ::Wire::Log::GetCoreLogger()->error(__VA_ARGS__)
#define WR_CORE_CRITICAL(...) ::Wire::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define WR_TRACE(...)         ::Wire::Log::GetClientLogger()->trace(__VA_ARGS__)
#define WR_INFO(...)          ::Wire::Log::GetClientLogger()->info(__VA_ARGS__)
#define WR_WARN(...)          ::Wire::Log::GetClientLogger()->warn(__VA_ARGS__)
#define WR_ERROR(...)         ::Wire::Log::GetClientLogger()->error(__VA_ARGS__)
#define WR_CRITICAL(...)      ::Wire::Log::GetClientLogger()->critical(__VA_ARGS__)
