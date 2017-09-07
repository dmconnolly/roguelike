#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include "tile_map.hpp"

class Game {
public:
	Game();
	~Game() = default;

	void step();

private:
	TileMap tile_map;
};

#endif /* GAME_HPP */
