#pragma once
#ifndef MAP_GENERATOR_HPP
#define MAP_GENERATOR_HPP

#include "tile_map.hpp"

class MapGenerator {
public:
    /* Delete constructor */
    MapGenerator() = delete;

    /* Delete destructor */
    ~MapGenerator() = delete;

    /* Delete copy constructors */
    MapGenerator(const MapGenerator &rhs) = delete;
    MapGenerator(MapGenerator &&rhs) = delete;

    /* Delete assignment operators */
    MapGenerator& operator=(const MapGenerator &rhs) = delete;
    MapGenerator& operator=(MapGenerator &&rhs) = delete;

    static void build(TileMap &map);

private:
    const static unsigned min_room_width = 5;
    const static unsigned max_room_width = 8;

    const static unsigned feature_goal = 20;
    const static unsigned max_feature_retries_pre_goal = 25;
    const static unsigned max_feature_retries_post_goal = 5;

    const static unsigned max_feature_start_tile_select_retries = 5;
    const static unsigned max_new_feature_start_mod = 30;
    const static unsigned min_passage_length = 8;
    const static unsigned max_passage_length = 25;

    const static unsigned min_entrance_exit_distance = 15;

    static void init_map(TileMap &map);
    static void add_start_room(TileMap &map);
    static void add_features(TileMap &map);
    static void correction_pass(TileMap &map);
    static void add_exit_stairs(TileMap &map);
};

#endif /* MAP_GENERATOR_HPP */
