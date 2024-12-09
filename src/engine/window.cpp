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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    monitor_ = glfwGetPrimaryMonitor();
    mode_ = glfwGetVideoMode(monitor_);

    if (config::get_config()["window"]["fullscreen"].as<bool>())
    {
        window_ = glfwCreateWindow(mode_->width, mode_->height, "Stellar Odyssey", monitor_, nullptr);
    }
    else 
    {
        const int width = config::get_config()["window"]["size"]["width"].as<int>();
        const int height = config::get_config()["window"]["size"]["height"].as<int>();
        window_ = glfwCreateWindow(width, height, "Stellar Odyssey", nullptr, nullptr);
    }

    if (window_ == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window_);
}

void window::update()
{
    while (!glfwWindowShouldClose(window_))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
}

void  window::cleanup()
{
    glfwDestroyWindow(window_);
    glfwTerminate();
}
