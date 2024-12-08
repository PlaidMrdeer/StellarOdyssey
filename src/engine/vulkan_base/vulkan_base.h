//
// Created by plaidmrdeer on 2024/12/8.
//

#ifndef VULKAN_BASE_H
#define VULKAN_BASE_H

#include <VkBootstrap.h>

class vulkan_base
{
public:
    void init();
private:
    VkSurfaceKHR surface = nullptr;

    vkb::InstanceBuilder instance_builder;
    vkb::Instance vkb_instance;

    void instance();
    void pickPhysicalDevice() const;
    void cleanup() const;
};

#endif