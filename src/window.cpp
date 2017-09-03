#include <cstdlib>

//#include "utils.hpp"
#include "window.hpp"

/// Minimal constructor
Window::Window() :
    cursor_locked(false),
    width(1024),
    height(768),
    title("Roguelike")
    //game()
{
    /* Empty */
}

/// Minimal destructor
Window::~Window() {
    //delete renderer;
}

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

	// Set callbacks
	glfwSetErrorCallback(error_callback);
	glfwSetFramebufferSizeCallback(glfw_window, reshape_callback);
	glfwSetCursorPosCallback(glfw_window, mouse_callback);
	glfwSetKeyCallback(glfw_window, key_callback);

	glfwMakeContextCurrent(glfw_window);

    // Turn on sticky keys
    glfwSetInputMode(glfw_window, GLFW_STICKY_KEYS, 1);

    // Normal cursor
    glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    // Store pointer in glfw window to this object
    glfwSetWindowUserPointer(glfw_window, this);

	/* Initialise glew */
	glewExperimental = true;
	if(glewInit() != GLEW_OK) {
		std::cerr << "glewInit() failed. Exiting\n";
		exit(EXIT_FAILURE);
	}

    // Show startup screen
    startup_screen();

    // Initialise renderer
    //renderer = new Renderer(width, height);

    // Enter event loop
    event_loop();
}

/// Reset the scene with new values
void Window::reset() {
    //delete renderer;

    // Initialise renderer
    //renderer = new Renderer(width, height);
}

/// Show startup screen
void Window::startup_screen() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glViewport(0, 0, width, height);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwSwapBuffers(glfw_window);
}

/// Main event loop

/// Get Renderer to check key input for per-frame usage \n
/// Get Renderer to draw the scene into buffer \n
/// Swap the buffers \n
/// Poll for new events
void Window::event_loop() {
    while(!glfwWindowShouldClose(glfw_window)) {
        check_input_frame(keys);
        //renderer->draw(game.get_state());
        glfwSwapBuffers(glfw_window);
        glfwPollEvents();
    }

    glfwTerminate();
}

/// Handle key presses when an event is triggered

/// This method is not called every frame, but only when \n
/// the key is pressed, release or repeated. This means that \n
/// there will be delays if a key is held down. This makes this \n
/// method ideal for controls such as toggling options.
void Window::input_key(int key, int action) {
    if(action != GLFW_PRESS && action != GLFW_REPEAT) {
        return;
    }

    // switch(key) {
    //     case GLFW_KEY_TAB:
    //         renderer->cycle_draw_mode();
    //     default:
    //         game.handle_input(key, action);
    // }
}

/// Handle key presses on a per-frame basis

/// This method is called every frame and takes an array of booleans \n
/// as a parameter, each bool represents whether a specific key is \n
/// currently pressed. As a result, this function allows actions to take \n
/// place every frame. This is ideal for smooth movement controls such as \n
/// moving the camera or light source.\n\n
/// Movement triggered through this function should use the frame delta time \n
/// to ensure that movement speed is the same across different platforms.
void Window::check_input_frame(bool *keys) {
    // if(keys[GLFW_KEY_KP_8]) {  }
    // if(keys[GLFW_KEY_KP_5]) {  }
    // if(keys[GLFW_KEY_KP_4]) {  }
    // if(keys[GLFW_KEY_KP_6]) {  }
    // if(keys[GLFW_KEY_KP_7]) {  }
    // if(keys[GLFW_KEY_KP_9]) {  }
}
