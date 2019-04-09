#pragma once
#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <array>
#include <memory>

#include "glm/glm.hpp"

#include "renderer.hpp"
#include "game_controller.hpp"

class Controller {
public:
    Controller(const int width, const int height);
    ~Controller() = default;

    // Delete copy constructors operators
    Controller(const Controller &rhs) = delete;
    Controller(Controller &&rhs) = delete;

    // Delete implicit assignment operators
    Controller& operator=(const Controller &rhs) = delete;
    Controller& operator=(Controller &&rhs) = delete;

    // Event handlers
    void window_resize(const int width, const int height);
    void key_input(const int key, const int scan_code,
        const int mods, const int action
    );
    void mouse_click(const int button, const int action,
        const int mods, const double x_pos, const double y_pos
    );

private:
    glm::ivec2 window_size;
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<GameController> game_controller;

    // Keys pressed on current frame
    const static unsigned int max_keys = 348;
    std::array<bool, max_keys> keys = { false };
};

#endif // CONTROLLER_HPP
