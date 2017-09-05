#pragma once
#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <array>
#include <memory>

#include "glm/glm.hpp"

#include "renderer.hpp"
#include "game_interface.hpp"

class Controller {
public:
	Controller(const int width, const int height);
	~Controller() = default;

	/* Event handlers */
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
	std::unique_ptr<GameInterface> game_interface;

	/* Keys pressed on current frame */
	const static unsigned int max_keys = 348;
	std::array<bool, max_keys> keys = { false };
};

#endif /* CONTROLLER_HPP */
