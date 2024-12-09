cmake_minimum_required(VERSION 3.15)
project(StellarOdyssey 
    LANGUAGES CXX 
    DESCRIPTION "StellarOdyssey，一个科幻题材的游戏" 
    VERSION 0.1.0
)

set(PROJECT_VERSION_SUFFIX "alpha")

# 基础配置
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # 禁用编译器特定扩展，确保更好的跨平台兼容性

# 输出目录设置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/StellarOdyssey/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/StellarOdyssey/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/StellarOdyssey/lib)

# 定义重要路径
set(CONFIG_DIR "${CMAKE_SOURCE_DIR}/config")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

# 收集源文件
file(GLOB_RECURSE CORE_SOURCE 
    "${SOURCE_DIR}/*.cpp"
    "${SOURCE_DIR}/*.h"
    "${INCLUDE_DIR}/*.h"
)

# 创建可执行文件
add_executable(${PROJECT_NAME} ${CORE_SOURCE})

# 添加编译选项
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE 
        -Wall 
        -Wextra 
        -Wpedantic 
        -Werror
    )
endif()

# 添加包含目录
target_include_directories(${PROJECT_NAME} PRIVATE
    ${SOURCE_DIR}
    ${INCLUDE_DIR}
)

# 复制配置文件
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CONFIG_DIR} $<TARGET_FILE_DIR:${PROJECT_NAME}>/config
)

# 设置FetchContent选项
set(FETCHCONTENT_QUIET OFF)
include(FetchContent)

# GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# GLM
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.9.8
)
FetchContent_MakeAvailable(glm)

# nlohmann-json
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)
set(JSON_BuildTests OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(json)

# yaml-cpp
FetchContent_Declare(
    yaml-cpp
    GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
    GIT_TAG yaml-cpp-0.7.0
)
set(YAML_CPP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(YAML_CPP_BUILD_TOOLS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(yaml-cpp)

# GLAD
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v0.1.36
)
set(GLAD_PROFILE "core" CACHE STRING "OpenGL profile")
set(GLAD_API "gl=4.6" CACHE STRING "API type/version pairs")
set(GLAD_GENERATOR "c" CACHE STRING "Language to generate the binding for")
FetchContent_MakeAvailable(glad)

# OpenGL
find_package(OpenGL REQUIRED)

# 链接所所有依赖
target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    glm
    nlohmann_json::nlohmann_json
    yaml-cpp
    OpenGL::GL
    glad
)

# 安装配置
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION StellarOdyssey/bin
    LIBRARY DESTINATION StellarOdyssey/lib
    ARCHIVE DESTINATION StellarOdyssey/lib
)

install(DIRECTORY ${CONFIG_DIR}
    DESTINATION StellarOdyssey/bin
)

# 添加测试支持（可选）
option(BUILD_TESTING "Build the testing tree." OFF)
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()