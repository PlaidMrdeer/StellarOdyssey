//
// Created by plaidmrdeer on 2024/12/8.
//

#include "vulkan_base.h"

#include <GLFW/glfw3.h>

#include "../window.h"

void vulkan_base::init()
{
    Init init;
    RenderData render_data;

    device_initialization(init);
    create_swapchain(init);
    get_queues(init, render_data);
}


int vulkan_base::device_initialization(Init& init) {
    vkb::InstanceBuilder instance_builder;
    auto instance_ret = instance_builder.use_default_debug_messenger().request_validation_layers().build();
    init.instance = instance_ret.value();

    init.inst_disp = init.instance.make_table();

    glfwCreateWindowSurface (init.instance, window::get_window(), nullptr, &init.surface);

    vkb::PhysicalDeviceSelector phys_device_selector(init.instance);
    auto phys_device_ret = phys_device_selector.set_surface(init.surface).select();
    const vkb::PhysicalDevice& physical_device = phys_device_ret.value();

    vkb::DeviceBuilder device_builder{ physical_device };
    auto device_ret = device_builder.build();
    init.device = device_ret.value();

    init.disp = init.device.make_table();

    return 0;
}

int vulkan_base::create_swapchain(Init& init) {

    vkb::SwapchainBuilder swapchain_builder{ init.device };
    auto swap_ret = swapchain_builder.set_old_swapchain(init.swapchain).build();
    destroy_swapchain(init.swapchain);
    init.swapchain = swap_ret.value();
    return 0;
}

int vulkan_base::get_queues(Init& init, RenderData& data) {
    auto gq = init.device.get_queue(vkb::QueueType::graphics);
    data.graphics_queue = gq.value();

    auto pq = init.device.get_queue(vkb::QueueType::present);
    data.present_queue = pq.value();
    return 0;
}