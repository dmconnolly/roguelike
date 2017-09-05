#pragma once
#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include <array>

class GameController{
public:
    GameController();
    ~GameController() = default;

    /* Event handlers */
    void window_resize(const int width, const int height);
    void key_input(const int key, const int scan_code,
        const int mods, const int action
    );
    void mouse_click(const int button, const int action,
        const int mods, const double x_pos, const double y_pos
    );

private:
    Renderer renderer;

    /* Keys pressed on current frame */
    const static max_keys = 348;
    std::array<bool, max_keys> keys = { false };
};

#endif /* GAME_CONTROLLER_HPP */
