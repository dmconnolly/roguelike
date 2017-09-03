#pragma once
#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>

#include "glbinding/Binding.h"
#include "GLFW/glfw3.h"

//#include "renderer.hpp"

/// Handles the glfw window

/// Initialises environment; creates window and sets callbacks
class Window {
public:
    /// Stores a pointer to the renderer
    //Renderer *renderer;
    /// Keys currently pressed on a per-frame basis
    bool keys[348] = { false };
    /// Whether cursor is locked (for camera movement)
    bool cursor_locked;

    Window();
    ~Window();
    void start();
    void event_loop();
    void reset();
private:
    /// Width of window
    int width;
    /// Height of window
    int height;
    /// Title of window
    char title[256];
    /// Pointer to glfw window
    GLFWwindow *glfw_window;

    void startup_screen();

    void input_key(int key, int action);
    void check_input_frame(bool *keys);

    /// Callback for errors
    inline static void error_callback(int error, const char *description) {
        std::cerr << description << '\n';
    }

    /// Callback for key presses
    inline static void key_callback(
        GLFWwindow *glfw_window,
        int key, int scan_code,
        int action, int mods)
    {
        Window *window = static_cast<Window *>(glfwGetWindowUserPointer(glfw_window));
        if(action == GLFW_PRESS) {
            if(key == GLFW_KEY_SPACE) {
                window->reset();
                return;
            }
            window->keys[key] = true;
        } else if(action == GLFW_RELEASE) {
            window->keys[key] = false;
        }
        window->input_key(key, action);
    }

    /// Callback for window resizing
    inline static void reshape_callback(GLFWwindow *glfw_window, int width, int height) {
        Window *window = static_cast<Window *>(glfwGetWindowUserPointer(glfw_window));
        glViewport(0, 0, width, height);
       // window->renderer->set_window_size(width, height);
    }

    /// Callback for mouse movement
    inline static void mouse_callback(GLFWwindow *glfw_window, double mouse_x, double mouse_y) {
        Window *window = static_cast<Window *>(glfwGetWindowUserPointer(glfw_window));
       // window->renderer->move_mouse(mouse_x, mouse_y);
    }
};

#endif /* WINDOW_HPP */
