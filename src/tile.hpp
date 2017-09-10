#pragma once
#ifndef TILE_HPP
#define TILE_HPP

#include <string>

#include "terrain.hpp"

class Tile {
public:
	const unsigned x;
	const unsigned y;
    const Terrain *terrain;

	/* Constructors */
    Tile(const unsigned x, const unsigned y, const Terrain *terrain=nullptr);
	Tile(const Tile &rhs);
	Tile(Tile &&rhs);
	~Tile() = default;

	/* Operator overloads */
	Tile& operator=(const Tile &rhs);
	Tile& operator=(Tile &&rhs);
};

#endif /* TILE_HPP */
