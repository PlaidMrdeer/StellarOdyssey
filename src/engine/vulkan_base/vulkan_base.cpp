//
// Created by plaidmrdeer on 2024/12/8.
//

#include "vulkan_base.h"

#include <GLFW/glfw3.h>

#include "../window.h"

void vulkan_base::init()
{
    instance();
    pickPhysicalDevice();
    cleanup();
}

void vulkan_base::instance()
{
    auto instance_builder_return = instance_builder
            .set_app_name ("Stellar Odyssey")
            .request_validation_layers()
            .use_default_debug_messenger()
            .require_api_version(1,3,0)
            .build();
    vkb_instance = instance_builder_return.value();
    glfwCreateWindowSurface (vkb_instance.instance, window::get_window(), nullptr, &surface);
}

void vulkan_base::pickPhysicalDevice() const
{
    vkb::PhysicalDeviceSelector phys_device_selector(vkb_instance);
    auto phys_ret = phys_device_selector.set_surface (surface)
                        .set_minimum_version (1, 3)
                        .require_dedicated_transfer_queue()
                        .select ();
}



void vulkan_base::cleanup() const
{
    vkDestroySurfaceKHR(vkb_instance, surface, nullptr);
    destroy_instance(vkb_instance);
}


