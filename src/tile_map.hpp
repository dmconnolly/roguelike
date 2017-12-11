#pragma once
#ifndef TILE_MAP_HPP
#define TILE_MAP_HPP

#include "tile_map_base.hpp"
#include "direction.hpp"
#include "terrain.hpp"
#include "tile.hpp"

class TileMap : TileMapBase {
public:
    struct Data {
        unsigned width;
        unsigned height;
        unsigned tile_count;
        Tile *entrance;
        Tile *exit;
        std::vector<Tile> tiles;
    };

    TileMap::Data *data;

    /* Constructor */
    TileMap(const unsigned width, const unsigned height);

    /* Destructor */
    ~TileMap();

    /* Delete copy constructors */
    TileMap(const TileMap &rhs) = delete;
    TileMap(TileMap &&rhs) = delete;

    /* Delete implicit assignment operators */
    TileMap& operator=(const TileMap &rhs) = delete;
    TileMap& operator=(TileMap &&rhs) = delete;

    /* Get tile by index */
    Tile& get(const unsigned x, const unsigned y) const;

    /* Get tile in direction from another tile */
    Tile& get(Tile &tile, const Direction direction) const;

    /* Returns a path between start and end */
    std::vector<Tile *> get_path(
        Tile &start, Tile &end,
        bool (*tile_pathable)(const Tile &),
        const bool diagonal_movement=false
    ) const;

    void save();
    void load();
    void print() const;

private:
    const unsigned id;

    unsigned manhattan_distance(const Tile &start, const Tile &end) const;
    unsigned chebyshev_distance(const Tile &start, const Tile &end) const;
};

#endif /* TILE_MAP_HPP */
