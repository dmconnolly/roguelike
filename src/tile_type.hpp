#pragma once
#ifndef TILE_TYPE_HPP
#define TILE_TYPE_HPP

#include <vector>
#include <cstddef>

#include "tile.hpp"

class TileType {
public:
	TileType() = delete;
	~TileType() = delete;
protected:
	const bool pathable;
};

#endif /* TILE_TYPE_HPP */
