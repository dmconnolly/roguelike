#include <cstdint>
#include <array>
#include <map>

#include "map_generator.hpp"
#include "random.hpp"
#include "terrain.hpp"

MapGenerator::MapGenerator(TileMap &map) :
    map(map),
    features(),
    assigned_tiles()
{
    features.reserve(feature_goal);
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
        entrance_pos[0] - (half_start_room_size[0] + start_room_size[0] % 2)-1,
        entrance_pos[1] - (half_start_room_size[1] + start_room_size[1] % 2)-1
    };

    const std::array<const unsigned, 2> end_pos = {
        entrance_pos[0] + (half_start_room_size[0] + start_room_size[0] % 2)-1,
        entrance_pos[1] + (half_start_room_size[1] + start_room_size[1] % 2)-1
    };

    features.push_back(Feature(Feature::Type::EntranceRoom));
    Feature &feature = features.back();

    for(unsigned y=start_pos[1]; y<=end_pos[1]; ++y) {
        for(unsigned x=start_pos[0]; x<=end_pos[0]; ++x) {
            Tile &tile = map.get(x, y);
            assigned_tiles[&tile] = &feature;
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

    features.push_back(std::move(feature));
}

bool MapGenerator::feature_fits(const Feature &feature) const {
    /* TODO */
    return true;
}

Feature::Type MapGenerator::get_feature_type() const {
    return Feature::Type::Room;
}

bool MapGenerator::add_room_feature(Feature &feature) {
    // Existing feature wall to connect to
    Feature &f = Random::from_vector(features);
    Tile &start_wall = *Random::from_vector(f.entrance_tiles);

    // Start corner of the room
    Tile &start_corner = map.get(
        Random::between(
            std::max(0, static_cast<int>(start_wall.x-max_new_feature_start_mod)),
            std::min(static_cast<int>(map.data->width-1), static_cast<int>(start_wall.x+max_new_feature_start_mod))
        ),
        Random::between(
            std::max(0, static_cast<int>(start_wall.y-max_new_feature_start_mod)),
            std::min(static_cast<int>(map.data->height-1), static_cast<int>(start_wall.y+max_new_feature_start_mod))
        )
    );

    // Random room size
    std::vector<unsigned> size = Random::between(min_room_width, max_room_width, 2);

    // Avoid going out of bounds
    const unsigned end_corner_x = start_corner.x + ((size[0]-1) * Random::one_of(-1, 1));
    const unsigned end_corner_y = start_corner.y + ((size[1]-1) * Random::one_of(-1, 1));

    // Out of bounds
    if(end_corner_x>map.data->width-1 || end_corner_y>map.data->height-1) {
        return false;
    }

    // End corner of the room
    Tile &end_corner = map.get(end_corner_x, end_corner_y);

    // Start and end values for the loop
    const unsigned min_x = std::min(start_corner.x, end_corner.x);
    const unsigned max_x = std::max(start_corner.x, end_corner.x);
    const unsigned min_y = std::min(start_corner.y, end_corner.y);
    const unsigned max_y = std::max(start_corner.y, end_corner.y);

    // Add all tiles to the feature
    for(unsigned y=min_y; y<=max_y; ++y) {
        for(unsigned x=min_x; x<=max_x; ++x) {
            Tile &tile = map.get(x, y);

            // Return if any tiles are already assigned
            if(assigned_tiles.count(&tile)) {
                return false;
            }

            feature.tiles.push_back(&tile);
            if(x==start_corner.x || x==end_corner.x || y==start_corner.y || y==end_corner.y) {
                // Tiles on the edge of the feature (walls)
                feature.edge_tiles.push_back(&tile);

                // Everything except the corners can be an entrance in future
                if((x != start_corner.x || y != start_corner.y) && 
                   (x != end_corner.x   || y != end_corner.y) &&
                   (x != start_corner.x || y != end_corner.y) &&
                   (x != end_corner.x   || y != start_corner.y))
                {
                    feature.entrance_tiles.push_back(&tile);
                }
            } else {
                // Tiles in the center of the feature (floors)
                feature.centre_tiles.push_back(&tile);
            }
        }
    }

    // Assign tile properties and assign to feature in map
    for(auto *tile : feature.edge_tiles) {
        assigned_tiles[tile] = &feature;
        tile->terrain = Terrain::get(Terrain::Type::StoneWall);
    }
    for(auto *tile : feature.centre_tiles) {
        assigned_tiles[tile] = &feature;
        tile->terrain = Terrain::get(Terrain::Type::StoneFloor);
    }

    return true;
}

void MapGenerator::correction_pass() {
    /* TODO */
}

void MapGenerator::add_exit_stairs() {
    /* TODO */
}
