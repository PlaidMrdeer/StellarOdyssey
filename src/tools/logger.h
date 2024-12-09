#ifndef LOGGER_H
#define LOGGER_H

#include "../engine/core.h"
#include <memory>
#include <spdlog/spdlog.h>

namespace stellar {
namespace utils {

class STELLAR_API Logger {
public:
    static void init(const std::string& logfile_path = "logs/stellar_odyssey.log");
    static void shutdown();

    static std::shared_ptr<spdlog::logger>& get_core_logger() { return s_core_logger; }
    static std::shared_ptr<spdlog::logger>& get_client_logger() { return s_client_logger; }

private:
    static std::shared_ptr<spdlog::logger> s_core_logger;
    static std::shared_ptr<spdlog::logger> s_client_logger;
};

} // namespace utils

// 核心日志宏
#define STELLAR_CORE_TRACE(...)    ::stellar::utils::Logger::get_core_logger()->trace(__VA_ARGS__)
#define STELLAR_CORE_INFO(...)     ::stellar::utils::Logger::get_core_logger()->info(__VA_ARGS__)
#define STELLAR_CORE_WARN(...)     ::stellar::utils::Logger::get_core_logger()->warn(__VA_ARGS__)
#define STELLAR_CORE_ERROR(...)    ::stellar::utils::Logger::get_core_logger()->error(__VA_ARGS__)
#define STELLAR_CORE_CRITICAL(...) ::stellar::utils::Logger::get_core_logger()->critical(__VA_ARGS__)

// 客户端日志宏
#define STELLAR_TRACE(...)         ::stellar::utils::Logger::get_client_logger()->trace(__VA_ARGS__)
#define STELLAR_INFO(...)          ::stellar::utils::Logger::get_client_logger()->info(__VA_ARGS__)
#define STELLAR_WARN(...)          ::stellar::utils::Logger::get_client_logger()->warn(__VA_ARGS__)
#define STELLAR_ERROR(...)         ::stellar::utils::Logger::get_client_logger()->error(__VA_ARGS__)
#define STELLAR_CRITICAL(...)      ::stellar::utils::Logger::get_client_logger()->critical(__VA_ARGS__)

} // namespace stellar

#endif // LOGGER_H