#include <iostream>
#include <string>

#include "GLFW/glfw3.h"

#include "game_controller.hpp"

GameController::GameController(Renderer &renderer) :
	renderer(renderer),
	game()
{
	/* Empty */
}

void GameController::step() {
	game.step();
}

void GameController::mouse_click(const int button, const int action,
    const int mods, const double x_pos, const double y_pos)
{
    /* Empty */
}

void GameController::key_input(const int key, const int scan_code,
    const int mods, const int action)
{
	/* Empty */
}
