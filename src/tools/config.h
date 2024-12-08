//
// Created by plaidmrdeer on 2024/12/8.
//

#ifndef CONFIG_H
#define CONFIG_H

#include <yaml-cpp/yaml.h>

class config
{
public:
    static YAML::Node get_config();
private:
    static YAML::Node config_;
};

#endif