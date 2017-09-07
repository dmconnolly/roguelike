#pragma once
#ifndef TILE_MAP_HPP
#define TILE_MAP_HPP

#include <vector>
#include <cstddef>

#include "tile.hpp"
#include "tile_type.hpp"

class TileMap {
public:
	const TileType *type;

	TileMap(const unsigned int width, const unsigned int height);
	~TileMap();
	Tile& get(const unsigned int idx);
	Tile& get(const unsigned int x, const unsigned int y);

private:
	const unsigned int width;
	const unsigned int height;
	const unsigned int tile_count;
	const std::size_t tile_size_bytes;
	const std::size_t width_bytes;
	std::vector<Tile> tiles;
};

#endif /* TILE_MAP_HPP */
