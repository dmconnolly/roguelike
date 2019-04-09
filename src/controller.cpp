#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include "controller.hpp"

Controller::Controller(const int width, const int height) :
    window_size(glm::ivec2(width, height))
{
    renderer = std::make_unique<Renderer>(window_size);
    game_controller = std::make_unique<GameController>(*renderer);
}

void Controller::window_resize(const int width, const int height) {
    window_size.x = width;
    window_size.y = height;
    renderer->window_resize(window_size);
}

void Controller::key_input(const int key, const int scan_code,
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

    // Do something with key
}

void Controller::mouse_click(const int button, const int action,
    const int mods, const double x_pos, const double y_pos)
{
    // Empty
}
