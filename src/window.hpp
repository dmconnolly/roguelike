#pragma once
#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <string>

#include "glbinding/Binding.h"
#include "GLFW/glfw3.h"

#include "game_controller.hpp"

class Window {
public:
    std::unique_ptr<GameController> game_controller;

    Window() = default;
    ~Window() = default;
    void start();
private:
    int width = 1024;
    int height = 768;
    std::string = "Roguelike";
    GLFWwindow *glfw_window = nullptr;
    bool cursor_locked = false;

    void check_input_frame();
    void event_loop();

    /// Callback for errors
    static void error_callback(int, const char *);
    static void key_callback(GLFWwindow *, int, int, int, int);
    static void resize_callback(GLFWwindow *, int, int);
    static void mouse_click_callback(GLFWwindow *, int, int, int);
};

#endif /* WINDOW_HPP */
