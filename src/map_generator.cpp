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
    // Empty
}

void MapGenerator::build() {
    init_map();
    add_hard_stone_walls();
    place_first_room();
    fill_with_rooms();
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

    room.connection_tile = &map.get(top_left_x + (width / 2), top_left_y + (height / 2));

    rooms.push_back(std::move(room));
}

void MapGenerator::fill_with_rooms() {
    // place_room_from_direction(Direction::South);
    for(unsigned fails=0; fails<max_consecutive_failed_room_placements;) {
        for(auto direction : cardinal_directions) {
            if(place_room_from_direction(direction)) {
                fails = 0;
            } else {
                ++fails;
            }
        }
    }
}

bool MapGenerator::place_room_from_direction(const Direction direction) {
    static const Terrain * const wall = Terrain::get(Terrain::Type::StoneWall);
    static const Terrain * const floor = Terrain::get(Terrain::Type::StoneFloor);

    const unsigned width = Random::between(min_room_width, max_room_width);
    const unsigned height = Random::between(min_room_width, max_room_width);

    unsigned bot_y;
    unsigned top_y;
    unsigned left_x;
    unsigned right_x;

    if(direction == Direction::South) {
        const unsigned y_limit = (map.data->height + 1) / 2;

        left_x = Random::between(room_buffer, (map.data->width - (room_buffer + width)) - 1);
        right_x = left_x + (width - 1);

        bot_y = map.data->height-1;
        top_y = bot_y - (height - 1);

        std::cout << "left_x: " << left_x << "\n";
        std::cout << "right_x: " << right_x << "\n";
        std::cout << "bot_y: " << bot_y << "\n";
        std::cout << "top_y: " << top_y << "\n\n";

        // First iteration so check full area around room for overlap
        for(unsigned y=top_y-room_buffer; y<=bot_y; ++y) {
            for(unsigned x=left_x-room_buffer; x<=right_x+room_buffer; ++x) {
                std::cout << "[" << x << "," << y << "]\n";
                if(assigned_tiles.count(&map.get(x, y))) {
                    // Failed to place room
                    return false;
                }
            }
        }

        std::cout << "\n";

        // Slide room into place
        for(unsigned tmp_top_y=top_y-1; tmp_top_y>=y_limit; --tmp_top_y) {
            // Only check leading edge
            const unsigned y = tmp_top_y - room_buffer;
            for(unsigned x=left_x-room_buffer; x<=right_x+room_buffer; ++x) {
                std::cout << "[" << x << "," << y << "]\n";
                if(assigned_tiles.count(&map.get(x, y))) {
                    goto end_room;
                }
            }

            --top_y;
            --bot_y;
        }
    } else if(direction == Direction::West) {
        const unsigned x_limit = (map.data->width - 1) / 2;

        left_x = 0;
        right_x = left_x + (width - 1);

        top_y = Random::between(room_buffer, (map.data->height - (room_buffer + height)) - 1);
        bot_y = top_y + (height - 1);

        // First iteration so check full area around room for overlap
        for(unsigned y=top_y-room_buffer; y<=bot_y+room_buffer; ++y) {
            for(unsigned x=left_x; x<=right_x+room_buffer; ++x) {
                if(assigned_tiles.count(&map.get(x, y))) {
                    // Failed to place room
                    return false;
                }
            }
        }

        // Slide room into place
        for(unsigned tmp_right_x=right_x+1; tmp_right_x<=x_limit; ++tmp_right_x) {
            // Only check leading edge
            const unsigned x = tmp_right_x + room_buffer;
            for(unsigned y=top_y-room_buffer; y<=bot_y+room_buffer; ++y) {
                if(assigned_tiles.count(&map.get(x, y))) {
                    goto end_room;
                }
            }

            ++left_x;
            ++right_x;
        }
    } else if(direction == Direction::North) {
        const unsigned y_limit = (map.data->height - 1) / 2;

        left_x = Random::between(room_buffer, (map.data->width - (room_buffer + width)) - 1);
        right_x = left_x + (width - 1);

        top_y = 0;
        bot_y = top_y + (height - 1);

        // First iteration so check full area around room for overlap
        for(unsigned y=top_y; y<=bot_y+room_buffer; ++y) {
            for(unsigned x=left_x-room_buffer; x<=right_x+room_buffer; ++x) {
                if(assigned_tiles.count(&map.get(x, y))) {
                    // Failed to place room
                    return false;
                }
            }
        }

        // Slide room into place
        for(unsigned tmp_bot_y=bot_y+1; tmp_bot_y<y_limit; ++tmp_bot_y) {
            // Only check leading edge
            const unsigned y = tmp_bot_y + room_buffer;
            for(unsigned x=left_x-room_buffer; x<=right_x+room_buffer; ++x) {
                if(assigned_tiles.count(&map.get(x, y))) {
                    goto end_room;
                }
            }

            ++top_y;
            ++bot_y;
        }
    } else if(direction == Direction::East) {
        const unsigned x_limit = (map.data->width + 1) / 2;

        right_x = map.data->width-1;
        left_x = right_x - (width - 1);

        top_y = Random::between(room_buffer, (map.data->height - (room_buffer + height)) - 1);
        bot_y = top_y + (height - 1);

        // First iteration so check full area around room for overlap
        for(unsigned y=top_y-room_buffer; y<=bot_y+room_buffer; ++y) {
            for(unsigned x=left_x-room_buffer; x<=right_x; ++x) {
                if(assigned_tiles.count(&map.get(x, y))) {
                    // Failed to place room
                    return false;
                }
            }
        }

        // Slide room into place
        for(unsigned tmp_left_x=left_x-1; tmp_left_x>=x_limit; --tmp_left_x) {
            // Only check leading edge
            const unsigned x = tmp_left_x - room_buffer;
            for(unsigned y=top_y-room_buffer; y<=bot_y+room_buffer; ++y) {
                if(assigned_tiles.count(&map.get(x, y))) {
                    goto end_room;
                }
            }

            --left_x;
            --right_x;
        }
    }

end_room:
    Room room;

    for(unsigned y=top_y; y<=bot_y; ++y) {
        for(unsigned x=left_x; x<=right_x; ++x) {
            Tile &tile = map.get(x, y);

            assigned_tiles.insert(&tile);
            room.tiles.push_back(&tile);

            if(x==left_x || x==right_x || y==top_y || y==bot_y) {
                room.edge_tiles.push_back(&tile);
            } else {
                room.centre_tiles.push_back(&tile);
                tile.terrain = floor;
            }
        }
    }

    room.connection_tile = &map.get(left_x + (width / 2), top_y + (height / 2));

    rooms.push_back(std::move(room));

    return true;
}

void MapGenerator::connect_rooms() {
    // TODO
}

void MapGenerator::add_water() {
    // TODO
}

void MapGenerator::add_pits() {
    // TODO
}

void MapGenerator::add_entrance_and_exit() {
    // TODO
}
