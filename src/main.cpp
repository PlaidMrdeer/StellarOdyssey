#include <iostream>

#include "engine/window.h"
#include "engine/vulkan_base/vulkan_base.h"

int main()
{
    window window_{};
    window_.run();

    vulkan_base vulkan_base_{};
    vulkan_base_.init();
}
