//
// Created by plaidmrdeer on 2024/12/7.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <GLFW/glfw3.h>

class window
{
public:
    void run();

    static GLFWwindow* get_window() ;
private:
    static GLFWwindow *window_;
    GLFWmonitor* monitor_ = nullptr;
    const GLFWvidmode *mode_ = nullptr;


    void init();
    static void update() ;
    static void cleanup() ;
};

#endif