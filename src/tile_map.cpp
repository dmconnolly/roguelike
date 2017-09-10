#include <sstream>
#include <iostream>

#include "tile_map.hpp"

constexpr static const Terrain create_terrain(const TileMap::TerrainType type) {
	bool pathable = false;
	bool pathable_flying = false;
	char ascii_char = '?';
	bool map_edge = false;

	switch(type) {
	case TileMap::TerrainType::MapEdge:
		pathable = false;
		pathable_flying = false;
		ascii_char = 'x';
		map_edge = true;
		break;
	case TileMap::TerrainType::StoneWall:
		pathable = false;
		pathable_flying = false;
		ascii_char = '+';
		break;
	case TileMap::TerrainType::StoneFloor:
		pathable = true;
		pathable_flying = true;
		ascii_char = '.';
		break;
	};

	return Terrain(
		pathable,
		pathable_flying,
		ascii_char,
		map_edge
	);
}

const std::map<const TileMap::TerrainType, const Terrain> TileMap::terrains = {
	{ TerrainType::MapEdge, create_terrain(TerrainType::MapEdge) },
	{ TerrainType::StoneWall, create_terrain(TerrainType::StoneWall) },
	{ TerrainType::StoneFloor, create_terrain(TerrainType::StoneFloor) }
};

const std::array<const TileMap::Direction, 8> TileMap::directions = {
	Direction::North, Direction::NorthEast,
	Direction::East, Direction::SouthEast,
	Direction::South, Direction::SouthWest,
	Direction::West, Direction::NorthWest
};

const std::array<const TileMap::Direction, 4> TileMap::cardinal_directions = {
	TileMap::Direction::North, TileMap::Direction::East,
	TileMap::Direction::South, TileMap::Direction::West
};

void TileMap::init(const unsigned width, const unsigned height) {
	this->width = width;
	this->height = height;
	tile_count = width * height;

	const long long tile_bytes = static_cast<long long>(sizeof Tile);
	const long long width_bytes = tile_bytes * width;

	init_tiles();

	tile_direction_offset.clear();
	tile_direction_offset.insert(std::pair<const Direction, const long long>(Direction::North, -width_bytes));
	tile_direction_offset.insert(std::pair<const Direction, const long long>(Direction::NorthEast, -width_bytes + tile_bytes));
	tile_direction_offset.insert(std::pair<const Direction, const long long>(Direction::East, tile_bytes));
	tile_direction_offset.insert(std::pair<const Direction, const long long>(Direction::SouthEast, width_bytes + tile_bytes));
	tile_direction_offset.insert(std::pair<const Direction, const long long>(Direction::South, width_bytes));
	tile_direction_offset.insert(std::pair<const Direction, const long long>(Direction::SouthWest, width_bytes - tile_bytes));
	tile_direction_offset.insert(std::pair<const Direction, const long long>(Direction::West, -tile_bytes));
	tile_direction_offset.insert(std::pair<const Direction, const long long>(Direction::NorthWest, -width_bytes - tile_bytes));
}

void TileMap::init_tiles() {
	const unsigned long edge_tile_count = ((width + 1) * 2) + ((height + 1) * 2);
	tiles.clear();
	tiles.reserve(tile_count + edge_tile_count);
	for(unsigned y=0; y<height+2; ++y) {
		for(unsigned x=0; x<width+2; ++x) {
			if(x==0 || x==width+1 || y==0 || y==height+1) {
				tiles.push_back(Tile(-1, -1, &terrains.at(TerrainType::MapEdge)));
			} else {
				tiles.push_back(Tile(x-1, y-1, &terrains.at(TerrainType::StoneWall)));
			}
		}
	}
}

Tile& TileMap::get(const unsigned x, const unsigned y) {
	return tiles[((width+2) * (1+y)) + (1+x)];
}

Tile& TileMap::get(Tile &tile, const Direction direction) {
	return *(&tile + tile_direction_offset[direction]);
}

const Tile& TileMap::get(const Tile &tile, const Direction direction) {
	return *(&tile + tile_direction_offset[direction]);
}

void TileMap::generate(const unsigned width, const unsigned height) {
	init(width, height);
}

void TileMap::save() {
	/* TODO */
}

void TileMap::load() {
	/* TODO */
}

std::vector<const Tile *> TileMap::get_path(Tile &start, Tile &end, bool diagonal_movement) {
	/* TODO */
	return std::vector<const Tile *>();
}

void TileMap::print() {
	std::stringstream ss;

	for(unsigned y=0; y<height; ++y) {
		for(unsigned x=0; x<width; ++x) {
			ss << get(x, y).terrain->ascii_char;
		}
		ss << '\n';
	}

	std::cout << ss.str() << '\n';
}
