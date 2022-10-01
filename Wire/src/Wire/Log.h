#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Wire {

	class WIRE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define WR_CORE_TRACE(...)    ::Wire::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define WR_CORE_INFO(...)     ::Wire::Log::GetCoreLogger()->info(__VA_ARGS__)
#define WR_CORE_WARN(...)     ::Wire::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define WR_CORE_ERROR(...)    ::Wire::Log::GetCoreLogger()->error(__VA_ARGS__)
#define WR_CORE_FATAL(...)    ::Wire::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define WR_TRACE(...)	      ::Wire::Log::GetClientLogger()->trace(__VA_ARGS__)
#define WR_INFO(...)	      ::Wire::Log::GetClientLogger()->info(__VA_ARGS__)
#define WR_WARN(...)	      ::Wire::Log::GetClientLogger()->warn(__VA_ARGS__)
#define WR_ERROR(...)	      ::Wire::Log::GetClientLogger()->error(__VA_ARGS__)
#define WR_FATAL(...)	      ::Wire::Log::GetClientLogger()->critical(__VA_ARGS__)