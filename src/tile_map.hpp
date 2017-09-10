#pragma once
#ifndef TILE_MAP_HPP
#define TILE_MAP_HPP

#include <map>
#include <array>
#include <vector>

#include "tile.hpp"
#include "terrain.hpp"

class TileMap {
public:
	/* Static data */
	enum class Direction : unsigned char {
		North, NorthEast,
		East, SouthEast,
		South, SouthWest,
		West, NorthWest
	};
	static const std::array<const Direction, 8> directions;
	static const std::array<const Direction, 4> cardinal_directions;

	enum class TerrainType : unsigned char {
		MapEdge, StoneWall, StoneFloor
	};

	/* Constructor */
	TileMap() = default;

	/* Destructor */
	~TileMap() = default;

	/* Delete copy constructors */
	TileMap(const TileMap &rhs) = delete;
	TileMap(TileMap &&rhs) = delete;

	/* Delete implicit assignment operators */
	TileMap& operator=(const TileMap &rhs) = delete;
	TileMap& operator=(TileMap &&rhs) = delete;

	/* Get tile by index */
	Tile& get(const unsigned x, const unsigned y);
	Tile& get(Tile &tile, const Direction direction);

	/* Get tile in direction from another tile */
	const Tile& get(const Tile &tile, const Direction direction);

	/* Generate a new tilemap */
	void generate(const unsigned width, const unsigned height);

	/* Save the tilemap to file */
	void save();

	/* Load the tilemap from file */
	void load();

	/* Returns a path between start and end */
	std::vector<const Tile *> get_path(Tile &start, Tile &end, bool diagonal_movement=false);

private:
	unsigned width;
	unsigned height;
	unsigned tile_count;
	std::map<const Direction, const long long> tile_direction_offset;
	static const std::map<const TerrainType, const Terrain> terrains;
	
	std::vector<Tile> tiles;

	void init(const unsigned width, const unsigned height);
	void init_tiles();
	void print();
};

#endif /* TILE_MAP_HPP */
