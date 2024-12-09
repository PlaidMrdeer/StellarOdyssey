#include "logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <iostream>

namespace stellar {
namespace utils {

std::shared_ptr<spdlog::logger> Logger::s_core_logger;
std::shared_ptr<spdlog::logger> Logger::s_client_logger;

void Logger::init(const std::string& logfile_path) {
    // 检查日志器是否已经初始化
    if (spdlog::get("STELLAR_CORE") != nullptr) {
        return;  // 如果已经初始化，直接返回
    }

    try {
        // 创建sink
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logfile_path, true);

        // 设置日志格式
        const std::string pattern = "[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] [%n] [%s:%#] %v";
        console_sink->set_pattern(pattern);
        file_sink->set_pattern(pattern);

        std::vector<spdlog::sink_ptr> sinks{console_sink, file_sink};

        // 创建核心日志器
        s_core_logger = std::make_shared<spdlog::logger>("STELLAR_CORE", sinks.begin(), sinks.end());
        s_core_logger->set_level(spdlog::level::trace);
        s_core_logger->flush_on(spdlog::level::trace);
        spdlog::register_logger(s_core_logger);

        // 创建客户端日志器
        s_client_logger = std::make_shared<spdlog::logger>("STELLAR_APP", sinks.begin(), sinks.end());
        s_client_logger->set_level(spdlog::level::trace);
        s_client_logger->flush_on(spdlog::level::trace);
        spdlog::register_logger(s_client_logger);

        STELLAR_CORE_INFO("日志系统初始化成功");
    }
    catch (const spdlog::spdlog_ex& ex) {
        std::cerr << "日志系统初始化失败: " << ex.what() << std::endl;
        throw;
    }
}

void Logger::shutdown() {
    spdlog::shutdown();
}

} // namespace utils
} // namespace stellar