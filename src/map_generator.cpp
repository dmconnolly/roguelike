#include "map_generator.hpp"
#include "terrain.hpp"

void MapGenerator::build(TileMap &map) {
    init_map(map);
    add_start_room(map);
    add_features(map);
    correction_pass(map);
    add_exit_stairs(map);
}

void MapGenerator::init_map(TileMap &map) {
    map.data->tiles.clear();
    map.data->tiles.reserve(map.data->tile_count + ((map.data->width + 1) * 2) + ((map.data->height + 1) * 2));
    for(unsigned y=0; y<map.data->height+2; ++y) {
        for(unsigned x=0; x<map.data->width+2; ++x) {
            if(x==0 || x==map.data->width+1 || y==0 || y==map.data->height+1) {
                map.data->tiles.push_back(Tile(
                    std::numeric_limits<decltype(x)>::max(),
                    std::numeric_limits<decltype(y)>::max(),
                    Terrain::get(Terrain::Type::MapEdge))
                );
            } else {
                map.data->tiles.push_back(Tile(x-1, y-1, Terrain::get(Terrain::Type::StoneFloor)));
            }
        }
    }
}

void MapGenerator::add_start_room(TileMap &map) {

}

void MapGenerator::add_features(TileMap &map) {

}

void MapGenerator::correction_pass(TileMap &map) {

}

void MapGenerator::add_exit_stairs(TileMap &map) {

}
