//
// Created by plaidmrdeer on 2024/12/8.
//

#ifndef CONFIG_H
#define CONFIG_H

#include "../engine/core.h"
#include <yaml-cpp/yaml.h>
#include <string>

namespace stellar {
namespace utils {

class STELLAR_API Config {
public:
    static Config& get_instance();
    
    static void init(const std::string& config_path = "config/config.yaml");
    const YAML::Node& get_config() const { return config_; }

private:
    Config() = default;
    ~Config() = default;
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;

    YAML::Node config_;
};

} // namespace utils
} // namespace stellar

#endif // CONFIG_H