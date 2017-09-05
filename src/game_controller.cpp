#include <iostream>
#include <string>

#include "GLFW/glfw3.h"

#include "game_controller.hpp"

GameController::GameController() {

}

void GameController::window_resize(const int width, const int height) {
    std::cout << "Window resized to " << width << "x" << height << '\n';
}

void GameController::mouse_move(const int button, const int action,
    const int mods, const double x_pos, const double y_pos)
{
    const std::string button_str = button == GLFW_MOUSE_BUTTON_RIGHT ? "Right" : "Left";
    const std::string action_str = action == GLFW_PRESS ? "pressed" : "released";
    std::cout << button_str << " mouse " << action_str <<
        " at [" << x_pos << "," y_pos << "]" << '\n';
}

void GameController::key_input(const int key, const int scan_code,
    const int mods, const int action)
{
    if(action == GLFW_PRESS) {
        keys[key] = true;
    } else if(action == GLFW_RELEASE) {
        keys[key] = false;
    }

    if(action != GLFW_PRESS && action != GLFW_REPEAT) {
        return;
    }

    std::cout << "Key '" << glfwGetKeyName(key, scan_code); << "' pressed\n";
}
