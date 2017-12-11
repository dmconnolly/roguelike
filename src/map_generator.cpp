#include <cstdint>
#include <limits>
#include <array>
#include <map>

#include "fastnoise/FastNoise.h"
#include "map_generator.hpp"
#include "random.hpp"
#include "terrain.hpp"

MapGenerator::MapGenerator(TileMap &map) :
    map(map),
    features(),
    assigned_tiles()
{
    /* Empty */
}

void MapGenerator::build() {
    init_map();
    add_hard_stone_walls();
    add_water();
    add_pits();
}

void MapGenerator::init_map() {
    map.data->tiles.clear();
    map.data->tiles.reserve(map.data->tile_count + ((map.data->width + 1) * 2) + ((map.data->height + 1) * 2));
    static const Terrain * const map_edge_ptr = Terrain::get(Terrain::Type::MapEdge);
    static const Terrain * const stone_wall_ptr = Terrain::get(Terrain::Type::StoneWall);

    for(unsigned y=0; y<map.data->height+2; ++y) {
        for(unsigned x=0; x<map.data->width+2; ++x) {
            if(x==0 || x==map.data->width+1 || y==0 || y==map.data->height+1) {
                map.data->tiles.push_back(Tile(
                    std::numeric_limits<decltype(x)>::max(),
                    std::numeric_limits<decltype(y)>::max(),
                    map_edge_ptr
                ));
            } else {
                map.data->tiles.push_back(Tile(x-1, y-1, stone_wall_ptr));
            }
        }
    }
}

void MapGenerator::add_hard_stone_walls() {
    //FastNoise noise_gen(Random::between(
    //    std::numeric_limits<int>::min(),
    //    std::numeric_limits<int>::max()
    //));
    FastNoise noise_gen(-1337);

    noise_gen.SetNoiseType(FastNoise::Perlin);
    noise_gen.SetFrequency(0.4);
    noise_gen.SetInterp(FastNoise::Interp::Quintic);

    static const Terrain * const hard_stone_wall_ptr = Terrain::get(Terrain::Type::HardStoneWall);

    for(unsigned y=0; y<map.data->height; ++y) {
        for(unsigned x=0; x<map.data->width; ++x) {
            const auto noise_val = noise_gen.GetNoise(x, y);
            if(noise_val > 0.3) {
                map.get(x, y).terrain = hard_stone_wall_ptr;
            }
        }
    }
}

void MapGenerator::place_first_room() {
    /* TODO */
}

void MapGenerator::place_all_rooms() {
    /* TODO */
}

void MapGenerator::connect_rooms() {
    /* TODO */
}

void MapGenerator::add_water() {
    /* TODO */
}

void MapGenerator::add_pits() {
    /* TODO */
}

void MapGenerator::add_entrance_and_exit() {
    /* TODO */
}
