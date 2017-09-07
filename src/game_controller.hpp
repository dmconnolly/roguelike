#pragma once
#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include <array>
#include <memory>

#include "glm/glm.hpp"

#include "renderer.hpp"
#include "game.hpp"

class GameController {
public:
	GameController(Renderer &renderer);
    ~GameController() = default;

	void step();

    /* Event handlers */
    void key_input(const int key, const int scan_code,
        const int mods, const int action
    );
    void mouse_click(const int button, const int action,
        const int mods, const double x_pos, const double y_pos
    );

private:
	Renderer &renderer;
	Game game;
};

#endif /* GAME_CONTROLLER_HPP */
