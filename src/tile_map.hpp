#pragma once
#ifndef TILE_MAP_HPP
#define TILE_MAP_HPP

#include <map>
#include <vector>
#include <random>

#include "pcg_random.hpp"

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
    static const std::vector<Direction> directions;
    static const std::vector<Direction> cardinal_directions;

    enum class TerrainType : unsigned char {
        MapEdge, StoneWall, StoneFloor
    };

    /* Constructor */
    TileMap(const unsigned id);
    TileMap(const unsigned id, const unsigned width, const unsigned height);

    /* Destructor */
    ~TileMap();

    /* Delete copy constructors */
    TileMap(const TileMap &rhs) = delete;
    TileMap(TileMap &&rhs) = delete;

    /* Delete implicit assignment operators */
    TileMap& operator=(const TileMap &rhs) = delete;
    TileMap& operator=(TileMap &&rhs) = delete;

    /* Get tile by index */
    Tile& get(const unsigned x, const unsigned y);

    /* Get tile in direction from another tile */
    Tile& get(Tile &tile, const Direction direction) const;
    const Tile& get(const Tile &tile, const Direction direction) const;

    /* Get terrain pointer */
    static const Terrain * const get(const TerrainType terrain);

    /* Generate a new tilemap */
    void generate();

    /* Save the tilemap to file */
    void save();

    /* Load the tilemap from file */
    void load();

    /* Returns a path between start and end */
    std::vector<Tile *> get_path(
        Tile &start, Tile &end,
        bool (*tile_pathable)(const Tile &),
        const bool diagonal_movement=false
    ) const;

    void print();

private:
    unsigned width;
    unsigned height;
    unsigned tile_count;
    unsigned id;
    std::map<const Direction, const long> tile_direction_offset;
    static const std::map<const TerrainType, const Terrain> terrains;

    std::vector<Tile> tiles;

    void init_direction_offsets();
    void init_tiles();
    unsigned manhattan_distance(const Tile &start, const Tile &end) const;
    unsigned chebyshev_distance(const Tile &start, const Tile &end) const;
};

#endif /* TILE_MAP_HPP */
