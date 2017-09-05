#pragma once
#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <memory>
#include <string>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "controller.hpp"

class Window {
public:
    std::unique_ptr<Controller> controller;

    Window();
    ~Window() = default;
    void start();
private:
    int width = 1024;
    int height = 768;
    std::string title;
    GLFWwindow *glfw_window = nullptr;
    bool cursor_locked = false;

    void event_loop();

    /// Callback for errors
    static void error_callback(int, const char *);
    static void key_callback(GLFWwindow *, int, int, int, int);
    static void resize_callback(GLFWwindow *, int, int);
    static void mouse_click_callback(GLFWwindow *, int, int, int);
};

#endif /* WINDOW_HPP */
