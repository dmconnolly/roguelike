#include "tile_map.hpp"

TileMap::TileMap(const unsigned int width, const unsigned int height) :
	width(width),
	height(height),
	tile_count(width * height),
	tile_size_bytes(sizeof Tile),
	width_bytes(tile_size_bytes * width),
	tiles(tile_count)
{
	/* Empty */
}

TileMap::~TileMap() {
	/* Empty */
}

Tile& TileMap::get(const unsigned int idx) {
	return tiles[idx];
}

Tile& TileMap::get(const unsigned int x, const unsigned int y) {
	return tiles[(width * y) + x];
}
