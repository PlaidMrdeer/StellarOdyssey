#include <iostream>
#include <glad/glad.h>
#include "engine/window.h"

int main()
{
    window window_{};
    window_.run();

    // 初始化 GLAD
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    return 0;
}
