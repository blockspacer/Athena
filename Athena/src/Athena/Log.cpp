#include "ath_pch.h"

#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace ath {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init() {
		// setting the way of printing each message
		spdlog::set_pattern("%^[%T] %n : %v%$");

		s_CoreLogger = spdlog::stdout_color_mt("Athena");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("App");
		s_ClientLogger->set_level(spdlog::level::trace);
		// @TODO
		// auto file_logger = spd::rotating_logger_mt("file_logger", "logs/mylogfile", 1048576 * 5, 3);
	}
}
