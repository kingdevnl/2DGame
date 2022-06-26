#pragma once
#include <spdlog/logger.h>


#define TRACE(...) spdlog::trace(__VA_ARGS__)
#define INFO(...) spdlog::info(__VA_ARGS__)
#define DEBUG(...) spdlog::debug(__VA_ARGS__)
#define WARN(...) spdlog::warn(__VA_ARGS__)
#define ERROR(...) spdlog::error(__VA_ARGS__)
#define CRITICAL(...) spdlog::critical(__VA_ARGS__)
