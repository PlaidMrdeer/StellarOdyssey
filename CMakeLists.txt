cmake_minimum_required(VERSION 3.30)
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

# GLFW
include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8
)
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
FetchContent_MakeAvailable(json)

# yaml-cpp
FetchContent_Declare(
    yaml-cpp
    GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
    GIT_TAG yaml-cpp-0.7.0
)
FetchContent_MakeAvailable(yaml-cpp)

# GLAD
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v0.1.36
)
set(GLAD_PROFILE "core" CACHE STRING "OpenGL profile")
set(GLAD_API "gl=4.6" CACHE STRING "API type/version pairs, like \"gl=3.2,gles=\", no version means latest")
set(GLAD_GENERATOR "c" CACHE STRING "Language to generate the binding for")
FetchContent_MakeAvailable(glad)

# OpenGL
find_package(OpenGL REQUIRED)

target_link_libraries(StellarOdyssey PRIVATE
    glfw
    glm
    nlohmann_json::nlohmann_json
    yaml-cpp
    OpenGL::GL
    glad
)