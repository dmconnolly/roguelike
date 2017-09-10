#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include "tile_map.hpp"

class Game {
public:
	Game();
	~Game() = default;

	/* Delete copy constructors operators */
	Game(const Game &rhs) = delete;
	Game(Game &&rhs) = delete;

	/* Delete implicit assignment operators */
	Game& operator=(const Game &rhs) = delete;
	Game& operator=(Game &&rhs) = delete;

	void start();
	void step();

private:
	TileMap tile_map;
};

#endif /* GAME_HPP */
