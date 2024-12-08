cmake_minimum_required(VERSION 3.30)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
project(StellarOdyssey LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/StellarOdyssey)

set(CONFIG_DIR "${CMAKE_SOURCE_DIR}/config")

file(GLOB_RECURSE CORE_SOURCE src/*.cpp src/*.h include/*.h)
add_executable(StellarOdyssey ${CORE_SOURCE})

add_custom_command(
        TARGET StellarOdyssey POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CONFIG_DIR} $<TARGET_FILE_DIR:StellarOdyssey>/config
)

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(vk-bootstrap CONFIG REQUIRED)

target_link_libraries(StellarOdyssey PRIVATE
        glfw
        glm::glm-header-only
        nlohmann_json::nlohmann_json
        yaml-cpp::yaml-cpp
        vk-bootstrap::vk-bootstrap vk-bootstrap::vk-bootstrap-compiler-warnings
)