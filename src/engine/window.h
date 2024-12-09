//
// Created by plaidmrdeer on 2024/12/7.
//

#ifndef WINDOW_H
#define WINDOW_H

#include "core.h"
#include <memory>
#include "renderer/renderer.h"

// 前向声明
struct GLFWwindow;
struct GLFWmonitor;
struct GLFWvidmode;

namespace stellar {

class STELLAR_API Window {
public:
    Window();
    ~Window();

    void init();
    void update();
    void cleanup();
    
    bool should_close() const;
    GLFWwindow* get_native_window() const { return window_; }
    void init_renderer();

private:
    GLFWwindow* window_;
    GLFWmonitor* monitor_;
    const GLFWvidmode* mode_;
    std::unique_ptr<Renderer> renderer_;
    std::shared_ptr<Shader> shader_;
};

} // namespace stellar

#endif // WINDOW_H