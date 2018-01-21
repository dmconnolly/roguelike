#pragma once
#ifndef MAP_GENERATOR_HPP
#define MAP_GENERATOR_HPP

#include "tile_map.hpp"
#include "room.hpp"

class MapGenerator {
public:
    /* Constructor */
    MapGenerator(TileMap &map);

    /* Default destructor */
    ~MapGenerator() = default;

    /* Delete copy constructors */
    MapGenerator(const MapGenerator &rhs) = delete;
    MapGenerator(MapGenerator &&rhs) = delete;

    /* Delete assignment operators */
    MapGenerator& operator=(const MapGenerator &rhs) = delete;
    MapGenerator& operator=(MapGenerator &&rhs) = delete;

    void build();

private:
    const static unsigned min_room_width = 6;
    const static unsigned max_room_width = 8;

    const static unsigned room_buffer = 2;

    const static unsigned min_room_connection_tiles = 1;
    const static unsigned max_room_connection_tiles = 3;

    TileMap &map;
    std::vector<Room> rooms;
    std::unordered_set<Tile *> assigned_tiles;

    void init_map();
    void add_hard_stone_walls();
    void place_first_room();
    void place_room();
    void place_all_rooms();
    void connect_rooms();
    void add_water();
    void add_pits();
    void add_entrance_and_exit();
};

#endif /* MAP_GENERATOR_HPP */
