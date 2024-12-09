#include "application.h"
#include "../engine/window.h"
#include "../tools/logger.h"
#include "../tools/config.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace stellar;

Application& Application::get_instance() {
    static Application instance;
    return instance;
}

void Application::init() {
    utils::Logger::init();
    STELLAR_CORE_INFO("StellarOdyssey 启动中...");
    
    // 初始化配置
    utils::Config::init();
    
    // 创建窗口
    window_ = std::make_unique<Window>();
    window_->init();
    
    // 初始化GLAD
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        STELLAR_CORE_CRITICAL("GLAD加载失败！");
        throw std::runtime_error("GLAD initialization failed");
    }
    
    STELLAR_CORE_INFO("GLAD初始化成功");
    is_running_ = true;
}

void Application::run() {
    init();
    
    while (is_running_ && !window_->should_close()) {
        window_->update();
    }
    
    shutdown();
}

void Application::shutdown() {
    window_->cleanup();
    utils::Logger::shutdown();
} 