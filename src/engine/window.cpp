//
// Created by plaidmrdeer on 2024/12/7.
//

#include "window.h"

#include <GLFW/glfw3.h>

#include "../tools/config.h"

YAML::Node config::config_ = YAML::LoadFile("config/config.yaml");
GLFWwindow* window::window_ = nullptr;

void window::run()
{
    init();
    update();
}

GLFWwindow *window::get_window()
{
    return window_;
}


void window::init()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    monitor_ = glfwGetPrimaryMonitor();
    mode_ = glfwGetVideoMode(monitor_);

    if (config::get_config()["window"]["fullscreen"].as<bool>())
    {
        window_ = glfwCreateWindow(mode_->width, mode_->height, "Stellar Odyssey", monitor_, nullptr);
        return;
    }

    const int width = config::get_config()["window"]["size"]["width"].as<int>();
    const int height = config::get_config()["window"]["size"]["height"].as<int>();
    window_ = glfwCreateWindow(width, height, "Stellar Odyssey", nullptr, nullptr);
}

void window::update()
{
    while (!glfwWindowShouldClose(window_))
    {
        glfwPollEvents();
    }
}

void  window::cleanup()
{
    glfwDestroyWindow(window_);
    glfwTerminate();
}
