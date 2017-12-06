#include <cstdint>
#include <array>
#include <map>

#include "map_generator.hpp"
#include "random.hpp"
#include "terrain.hpp"

MapGenerator::MapGenerator(TileMap &map) :
    map(map),
    features(feature_goal),
    tile_features()
{
    init_map();
    add_start_room();
    add_features();
    correction_pass();
    add_exit_stairs();
}

void MapGenerator::build() {
    init_map();
    add_start_room();
    add_features();
    correction_pass();
    add_exit_stairs();
}

void MapGenerator::init_map() {
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
                map.data->tiles.push_back(Tile(x-1, y-1, Terrain::get(Terrain::Type::StoneWall)));
            }
        }
    }
}

void MapGenerator::add_start_room() {
    const std::vector<unsigned> start_room_size = Random::between(
        min_room_width, max_room_width, 2
    );

    const std::array<const unsigned, 2> half_start_room_size = {
        start_room_size[0]/2,
        start_room_size[1]/2
    };

    const std::array<const unsigned, 2> entrance_pos = {
        Random::between(
            half_start_room_size[0] + start_room_size[0] % 2,
            map.data->width - half_start_room_size[0] - 2
        ),
        Random::between(
            half_start_room_size[1] + start_room_size[1] % 2,
            map.data->height - half_start_room_size[1] - 2
        )
    };

    const std::array<const unsigned, 2> start_pos = {
        entrance_pos[0] - (half_start_room_size[0] + start_room_size[0] % 2),
        entrance_pos[1] - (half_start_room_size[1] + start_room_size[1] % 2)
    };

    const std::array<const unsigned, 2> end_pos = {
        entrance_pos[0] + (half_start_room_size[0] + start_room_size[0] % 2),
        entrance_pos[1] + (half_start_room_size[1] + start_room_size[1] % 2)
    };

    features.push_back(Feature(Feature::Type::EntranceRoom));
    Feature &feature = features.back();

    for(unsigned y=start_pos[1]; y<=end_pos[1]; ++y) {
        for(unsigned x=start_pos[0]; x<=end_pos[0]; ++x) {
            Tile &tile = map.get(x, y);
            tile_features[&tile] = &feature;
            feature.tiles.push_back(&tile);

            if(x==start_pos[0] || x==end_pos[0] || y==start_pos[1] || y==end_pos[1]) {
                tile.terrain = Terrain::get(Terrain::Type::StoneWall);
                feature.edge_tiles.push_back(&tile);

                if((x != start_pos[0] || y != start_pos[1]) && 
                   (x != end_pos[0]   || y != end_pos[1]) &&
                   (x != start_pos[0] || y != end_pos[1]) &&
                   (x != end_pos[0]   || y != start_pos[1]))
                {
                    feature.entrance_tiles.push_back(&tile);
                }
            } else {
                tile.terrain = Terrain::get(Terrain::Type::StoneFloor);
                feature.centre_tiles.push_back(&tile);
            }
        }
    }

    map.data->entrance = &map.get(entrance_pos[0], entrance_pos[1]);
}

void MapGenerator::add_features() {
    int max_retries = max_feature_retries_pre_goal;
    int retries = 0;

    while(retries <= max_retries) {
        retries += try_add_feature() ? 0 : 1;
        if(features.size() == feature_goal) {
            max_retries = max_feature_retries_post_goal;
        }
    }
}

bool MapGenerator::try_add_feature() {
    Tile &start_wall = *Random::from_vector(Random::from_vector(features).entrance_tiles);
    Feature feature(get_feature_type());

    switch(feature.type) {
        case Feature::Type::Room:
            if(!add_room_feature(feature)) {
                return false;
            }
        default:
            /* TODO: Special features */
            return false;
    }
}

bool MapGenerator::feature_fits(const Feature &feature) const {
    /* TODO */
    return true;
}

Feature::Type MapGenerator::get_feature_type() const {
    return Feature::Type::Room;
}

bool MapGenerator::add_room_feature(Feature &feature) {
    /* TODO */
}

void MapGenerator::correction_pass() {
    /* TODO */
}

void MapGenerator::add_exit_stairs() {
    /* TODO */
}
