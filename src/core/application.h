#ifndef APPLICATION_H
#define APPLICATION_H

#include "../engine/core.h"
#include <memory>

namespace stellar {

class Window;  // 前向声明

class STELLAR_API Application {
public:
    static Application& get_instance();
    
    void run();
    void shutdown();
    
    Window& get_window() { return *window_; }

private:
    Application() = default;
    ~Application() = default;
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    void init();
    
    std::unique_ptr<Window> window_;
    bool is_running_ = false;
};

} // namespace stellar

#endif // APPLICATION_H 