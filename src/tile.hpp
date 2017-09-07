#pragma once
#ifndef TILE_HPP
#define TILE_HPP

#include <string>

class Tile {
public:
	/* Constructors */
	Tile();
	Tile(const Tile &rhs);
	Tile(Tile &&rhs);
	~Tile() = default;

	/* Operator overloads */
	Tile& operator=(const Tile &rhs);
	Tile& operator=(Tile &&rhs);
};

#endif /* TILE_HPP */
