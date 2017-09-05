#include <iostream>
#include <string>

#include "GLFW/glfw3.h"

#include "game_interface.hpp"

GameInterface::GameInterface(Renderer &renderer) : 
	renderer(renderer)
{
	/* Empty */
}

void GameInterface::mouse_click(const int button, const int action,
    const int mods, const double x_pos, const double y_pos)
{
    /* Empty */
}

void GameInterface::key_input(const int key, const int scan_code,
    const int mods, const int action)
{
	/* Empty */
}
