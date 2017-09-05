#include <cstdlib>

#include "glbinding/gl/functions.h"
#include "glbinding/gl/enum.h"

#include "window.hpp"

/// Initialises the window

/// Initialise glfw \n
/// Create glfw window
/// Obtain OpenGL context and assign to glfw window \n
/// Initialise glew \n
/// Set glfw window parameters \n
/// Set callbacks in window \n
/// Initialise Renderer instance \n
/// Enter event loop \n
void Window::start() {
    // Set error callback
    glfwSetErrorCallback(error_callback);

	if(glfwInit() != GLFW_TRUE) {
		std::cerr << "glfwInit() failed. Exiting\n";
		exit(EXIT_FAILURE);
	}

	// Window hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    // Create glfw window
    glfw_window = glfwCreateWindow(width, height, title, NULL, NULL);
    if(!glfw_window) {
        std::cerr << "GLFW failed to create window\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

	// Set event callbacks
    glfwSetMouseButtonCallback(glfw_window, mouse_click_callback);
	glfwSetFramebufferSizeCallback(glfw_window, resize_callback);
	glfwSetKeyCallback(glfw_window, key_callback);

	glfwMakeContextCurrent(glfw_window);

    // Turn on sticky keys
    glfwSetInputMode(glfw_window, GLFW_STICKY_KEYS, 1);

    // Normal cursor
    glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    // Store pointer in glfw window to this object
    glfwSetWindowUserPointer(glfw_window, this);

    // Initialise game controller just before entering event loop
    game_controller = std::make_unique<GameController>();

    // Enter event loop
    event_loop();
}

/// Main event loop

/// Get Renderer to check key input for per-frame usage \n
/// Get Renderer to draw the scene into buffer \n
/// Swap the buffers \n
/// Poll for new events
void Window::event_loop() {
    while(!glfwWindowShouldClose(glfw_window)) {
        check_input_frame(keys);
        glfwSwapBuffers(glfw_window);
        glfwPollEvents();
    }
    glfwTerminate();
}

void Window::error_callback(int error, const char *description) {
    std::cerr << "GLFW error: " << error << " - " << description << '\n';
}

void Window::key_callback(
    GLFWwindow *glfw_window,
    int key, int scan_code,
    int action, int mods)
{
    Window &window = *static_cast<Window *>(glfwGetWindowUserPointer(glfw_window));
    window.game_controller.key_input(key, scan_code, mods, action);
}

void Window::resize_callback(GLFWwindow *glfw_window, int width, int height) {
    Window &window = *static_cast<Window *>(glfwGetWindowUserPointer(glfw_window));
    window.game_controller.window_resize(width, height);
}

void Window::mouse_click_callback(GLFWwindow *window, int button, int action, int mods) {
    Window &window = *static_cast<Window *>(glfwGetWindowUserPointer(glfw_window));
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    window.game_controller.mouse_click(button, action, mods, x, y);
}
