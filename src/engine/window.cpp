//
// Created by plaidmrdeer on 2024/12/7.
//

#include "window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../tools/config.h"
#include "../tools/logger.h"
#include "renderer/shader.h"
#include "renderer/renderer.h"

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
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        STELLAR_CORE_CRITICAL("GLAD初始化失败");
        throw std::runtime_error("Failed to initialize GLAD");
    }
    
    init_renderer();
}

void Window::init_renderer() {
    renderer_ = std::make_unique<Renderer>();
    renderer_->init();
    
    shader_ = std::make_shared<Shader>("shaders/basic.vert", "shaders/basic.frag");
    renderer_->set_shader(shader_);
}

void Window::update() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // 在每一帧都绘制三角形
    std::vector<Vertex> vertices = {
        {{-0.5f, -0.5f, 0.0f}},
        {{ 0.5f, -0.5f, 0.0f}},
        {{ 0.0f,  0.5f, 0.0f}}
    };
    
    renderer_->begin_batch();
    renderer_->draw_vertices(vertices);
    renderer_->end_batch();

    glfwSwapBuffers(window_);
    glfwPollEvents();
}

void Window::cleanup() {
    renderer_.reset();
    shader_.reset();
    
    if (window_) {
        glfwDestroyWindow(window_);
        window_ = nullptr;
    }
    glfwTerminate();
}

bool Window::should_close() const {
    return glfwWindowShouldClose(window_);
}
