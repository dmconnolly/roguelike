#include <unordered_map>
#include <cstdint>
#include <limits>
#include <array>
#include <fstream>
#include <string>

#include "fastnoise/FastNoise.h"
#include "map_generator.hpp"
#include "random.hpp"
#include "terrain.hpp"

MapGenerator::MapGenerator(TileMap &map) :
    map(map),
    rooms(),
    assigned_tiles()
{
    /* Empty */
}

void MapGenerator::build() {
    init_map();
    add_hard_stone_walls();
    place_first_room();
    place_all_rooms();
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
    FastNoise noise_gen(Random::between(
        std::numeric_limits<int>::min(),
        std::numeric_limits<int>::max()
    ));

    noise_gen.SetNoiseType(FastNoise::Perlin);
    noise_gen.SetFrequency(static_cast<FN_DECIMAL>(0.4));
    noise_gen.SetInterp(FastNoise::Interp::Quintic);

    static const Terrain * const hard_stone_wall_ptr = Terrain::get(Terrain::Type::HardStoneWall);

    for(unsigned y=0; y<map.data->height; ++y) {
        for(unsigned x=0; x<map.data->width; ++x) {
            const auto noise_val = noise_gen.GetNoise(
                static_cast<FN_DECIMAL>(x),
                static_cast<FN_DECIMAL>(y)
            );
            if(noise_val > 0.3) {
                map.get(x, y).terrain = hard_stone_wall_ptr;
            }
        }
    }
}

void MapGenerator::place_first_room() {
    Room room;

    const unsigned width = Random::between(min_room_width, max_room_width);
    const unsigned height = Random::between(min_room_width, max_room_width);

    const unsigned top_left_x = Random::between(room_buffer, (map.data->width - (room_buffer + width)) - 1);
    const unsigned top_left_y = Random::between(room_buffer, (map.data->height - (room_buffer + height)) - 1);

    const unsigned bot_right_x = (top_left_x + width) - 1;
    const unsigned bot_right_y = (top_left_y + height) - 1;

    const unsigned connection_tiles = Random::between(min_room_connection_tiles, max_room_connection_tiles);

    const static Terrain * const wall = Terrain::get(Terrain::Type::StoneWall);
    const static Terrain * const floor = Terrain::get(Terrain::Type::StoneFloor);

    for(unsigned y=top_left_y; y<=bot_right_y; ++y) {
        for(unsigned x=top_left_x; x<=bot_right_x; ++x) {
            Tile &tile = map.get(x, y);

            assigned_tiles.insert(&tile);
            room.tiles.push_back(&tile);

            if(x==top_left_x || x==bot_right_x || y==top_left_y || y==bot_right_y) {
                room.edge_tiles.push_back(&tile);
                tile.terrain = wall;
            } else {
                room.centre_tiles.push_back(&tile);
                tile.terrain = floor;
            }
        }
    }

    for(unsigned i=0; i<connection_tiles; ++i) {
        Tile *tile;
        do {
            tile = Random::from_vector(room.edge_tiles);
        } while(std::find(room.connection_tiles.begin(),
            room.connection_tiles.end(), tile) != room.connection_tiles.end());
        room.connection_tiles.push_back(tile);
    }

    rooms.push_back(std::move(room));
}

void MapGenerator::place_all_rooms() {
    const static Terrain * const wall = Terrain::get(Terrain::Type::StoneWall);
    const static Terrain * const floor = Terrain::get(Terrain::Type::StoneFloor);

    for(unsigned consecutive_fails=0; consecutive_fails<cardinal_directions.size();) {
        for(auto direction : cardinal_directions) {
            const unsigned width = Random::between(min_room_width, max_room_width);
            const unsigned height = Random::between(min_room_width, max_room_width);

            if(direction == Direction::South) {
                const unsigned left_x = Random::between(room_buffer, (map.data->width - (room_buffer + width)) - 1);
                const unsigned right_x = left_x + (width - 1);
                const unsigned y_limit = (map.data->height + 1) / 2;

                unsigned bot_y = map.data->height-1;
                unsigned top_y = bot_y-height;

                bool success = false;
                for(unsigned tmp_top_y=top_y; tmp_top_y>=y_limit; --tmp_top_y) {
                   bool fits = true;

                   if(!success) {
                       // First iteration so check full area around room for overlap
                       for(unsigned y=tmp_top_y-room_buffer; y<=bot_y && fits; ++y) {
                           for(unsigned x=left_x-room_buffer; x<=right_x+room_buffer && fits; ++x) {
                               if(assigned_tiles.count(&map.get(x, y))) {
                                   fits = false;
                               }
                           }
                       }
                   } else {
                       // Only check leading edge each of room as it slides into place
                       unsigned y = tmp_top_y - room_buffer;
                       for(unsigned x=left_x-room_buffer; x<=right_x+room_buffer && fits; ++x) {
                           if(assigned_tiles.count(&map.get(x, y))) {
                               fits = false;
                           }
                       }
                   }

                   if(fits) {
                       --top_y;
                       --bot_y;
                       success = true;
                   } else {
                       break;
                   }
                }

                if(success) {
                   const unsigned connection_tiles = Random::between(min_room_connection_tiles, max_room_connection_tiles);
                   Room room;

                   for(unsigned y=top_y; y<=bot_y; ++y) {
                       for(unsigned x=left_x; x<=right_x; ++x) {
                           Tile &tile = map.get(x, y);

                           assigned_tiles.insert(&tile);
                           room.tiles.push_back(&tile);

                           if(x==left_x || x==right_x || y==top_y || y==bot_y) {
                               room.edge_tiles.push_back(&tile);
                               tile.terrain = wall;
                           } else {
                               room.centre_tiles.push_back(&tile);
                               tile.terrain = floor;
                           }
                       }
                   }

                   rooms.push_back(std::move(room));
                   consecutive_fails = 0;
                } else {
                   ++consecutive_fails;
                }
            } else if(direction == Direction::West) {

            } else if(direction == Direction::North) {
                const unsigned left_x = Random::between(room_buffer, (map.data->width - (room_buffer + width)) - 1);
                const unsigned right_x = left_x + (width - 1);
                const unsigned y_limit = (map.data->height - 1) / 2;

                unsigned top_y = 0;
                unsigned bot_y = top_y + (height - 1);

                bool success = false;
                for(unsigned tmp_bot_y=bot_y; tmp_bot_y<y_limit; ++tmp_bot_y) {
                    bool fits = true;

                    if(!success) {
                        // First iteration so check full area around room for overlap
                        for(unsigned y=top_y; y<=tmp_bot_y+room_buffer && fits; ++y) {
                            for(unsigned x=left_x-room_buffer; x<=right_x+room_buffer && fits; ++x) {
                                if(assigned_tiles.count(&map.get(x, y))) {
                                    fits = false;
                                }
                            }
                        }
                    } else {
                        // Only check leading edge each of room as it slides into place
                        unsigned y = tmp_bot_y + room_buffer;
                        for(unsigned x=left_x-room_buffer; x<=right_x+room_buffer && fits; ++x) {
                            if(assigned_tiles.count(&map.get(x, y))) {
                                fits = false;
                            }
                        }
                    }

                    if(fits) {
                        ++top_y;
                        ++bot_y;
                        success = true;
                    } else {
                        break;
                    }
                }

                if(success) {
                    const unsigned connection_tiles = Random::between(min_room_connection_tiles, max_room_connection_tiles);
                    Room room;

                    for(unsigned y=top_y; y<=bot_y; ++y) {
                        for(unsigned x=left_x; x<=right_x; ++x) {
                            Tile &tile = map.get(x, y);

                            assigned_tiles.insert(&tile);
                            room.tiles.push_back(&tile);

                            if(x==left_x || x==right_x || y==top_y || y==bot_y) {
                                room.edge_tiles.push_back(&tile);
                                tile.terrain = wall;
                            } else {
                                room.centre_tiles.push_back(&tile);
                                tile.terrain = floor;
                            }
                        }
                    }

                    rooms.push_back(std::move(room));
                    consecutive_fails = 0;
                } else {
                    ++consecutive_fails;
                }
            } else if(direction == Direction::East) {

            }
        }
    }
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
