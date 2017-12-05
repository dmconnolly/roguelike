#pragma once
#ifndef MAP_GENERATOR_HPP
#define MAP_GENERATOR_HPP

#include "tile_map.hpp"
#include "feature.hpp"

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

    TileMap &map;
    std::vector<Feature> features;
    std::map<Tile *, Feature *> tile_features;

    void init_map();
    void add_start_room();
    void add_features();
    void correction_pass();
    void add_exit_stairs();
};

#endif /* MAP_GENERATOR_HPP */
