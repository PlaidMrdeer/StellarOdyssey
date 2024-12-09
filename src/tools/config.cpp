//
// Created by plaidmrdeer on 2024/12/8.
//

#include "config.h"
#include "logger.h"

namespace stellar {
namespace utils {

Config& Config::get_instance() {
    static Config instance;
    return instance;
}

void Config::init(const std::string& config_path) {
    try {
        Config::get_instance().config_ = YAML::LoadFile(config_path);
        STELLAR_CORE_INFO("配置文件加载成功");
    } catch (const YAML::Exception& e) {
        STELLAR_CORE_CRITICAL("配置文件加载失败: {}", e.what());
        throw;
    }
}

} // namespace utils
} // namespace stellar
