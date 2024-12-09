//
// Created by plaidmrdeer on 2024/12/7.
//

#include "window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../tools/config.h"
#include "../tools/logger.h"

using namespace stellar;

Window::Window() : window_(nullptr), monitor_(nullptr), mode_(nullptr) {}

Window::~Window() {
    cleanup();
}

void Window::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    monitor_ = glfwGetPrimaryMonitor();
    mode_ = glfwGetVideoMode(monitor_);

    const auto& config = utils::Config::get_instance().get_config();
    
    if (config["window"]["fullscreen"].as<bool>()) {
        window_ = glfwCreateWindow(mode_->width, mode_->height, 
                                 "Stellar Odyssey", monitor_, nullptr);
    } else {
        const int width = config["window"]["size"]["width"].as<int>();
        const int height = config["window"]["size"]["height"].as<int>();
        window_ = glfwCreateWindow(width, height, 
                                 "Stellar Odyssey", nullptr, nullptr);
    }

    if (window_ == nullptr) {
        STELLAR_CORE_CRITICAL("GLFW窗口创建失败！");
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window_);
}

void Window::update() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window_);
    glfwPollEvents();
}

void Window::cleanup() {
    if (window_) {
        glfwDestroyWindow(window_);
        window_ = nullptr;
    }
    glfwTerminate();
}

bool Window::should_close() const {
    return glfwWindowShouldClose(window_);
}
