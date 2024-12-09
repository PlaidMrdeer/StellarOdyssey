#include "core/application.h"
#include "tools/logger.h"

using namespace stellar;

int main() {
    try {
        utils::Logger::init();
        STELLAR_CORE_INFO("StellarOdyssey引擎启动");
        
        Application::get_instance().run();
        
        STELLAR_CORE_INFO("StellarOdyssey引擎关闭");
    } catch (const std::exception& e) {
        STELLAR_CORE_CRITICAL("程序异常退出: {}", e.what());
        return -1;
    }
    
    return 0;
}
