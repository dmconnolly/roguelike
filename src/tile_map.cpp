#include <sstream>
#include <iostream>
#include <limits>
#include <functional>
#include <unordered_set>
#include <queue>
#include <deque>
#include <cstdint>
#include <algorithm>

#include "tile_map.hpp"

template <template<class, class, class...> class C, typename K, typename V, typename... Args>
V get_with_default(const C<K, V, Args...> &m, K const &key, const V &default_val) {
    typename C<K, V, Args...>::const_iterator it = m.find(key);
    return it == m.end() ? default_val : it->second;
}

constexpr static const Terrain create_terrain(const TileMap::TerrainType type) {
    bool pathable = false;
    bool pathable_flying = false;
    char ascii_char = '?';
    bool map_edge = false;

    switch(type) {
        case TileMap::TerrainType::MapEdge:
            pathable = false;
            pathable_flying = false;
            ascii_char = 'x';
            map_edge = true;
            break;
        case TileMap::TerrainType::StoneWall:
            pathable = false;
            pathable_flying = false;
            ascii_char = '+';
            break;
        case TileMap::TerrainType::StoneFloor:
            pathable = true;
            pathable_flying = true;
            ascii_char = '.';
            break;
    };

    return Terrain(
        pathable,
        pathable_flying,
        ascii_char,
        map_edge
    );
}

const std::map<const TileMap::TerrainType, const Terrain> TileMap::terrains = {
    { TerrainType::MapEdge, create_terrain(TerrainType::MapEdge) },
    { TerrainType::StoneWall, create_terrain(TerrainType::StoneWall) },
    { TerrainType::StoneFloor, create_terrain(TerrainType::StoneFloor) }
};

const std::vector<TileMap::Direction> TileMap::directions = {
    Direction::North, Direction::NorthEast,
    Direction::East, Direction::SouthEast,
    Direction::South, Direction::SouthWest,
    Direction::West, Direction::NorthWest
};

const std::vector<TileMap::Direction> TileMap::cardinal_directions = {
    TileMap::Direction::North, TileMap::Direction::East,
    TileMap::Direction::South, TileMap::Direction::West
};

void TileMap::init(const unsigned map_width, const unsigned map_height) {
    this->width = width;
    this->height = height;
    tile_count = width * height;

    init_tiles();

    const long width_signed = static_cast<long>(width + 2);
    tile_direction_offset.clear();
    tile_direction_offset.insert(std::pair<const Direction, const long>(Direction::North, -width_signed));
    tile_direction_offset.insert(std::pair<const Direction, const long>(Direction::NorthEast, -width_signed + 1));
    tile_direction_offset.insert(std::pair<const Direction, const long>(Direction::East, 1));
    tile_direction_offset.insert(std::pair<const Direction, const long>(Direction::SouthEast, width_signed + 1));
    tile_direction_offset.insert(std::pair<const Direction, const long>(Direction::South, width_signed));
    tile_direction_offset.insert(std::pair<const Direction, const long>(Direction::SouthWest, width_signed - 1));
    tile_direction_offset.insert(std::pair<const Direction, const long>(Direction::West, -1));
    tile_direction_offset.insert(std::pair<const Direction, const long>(Direction::NorthWest, -width_signed - 1));
}

void TileMap::init_tiles() {
    tiles.clear();
    tiles.reserve(tile_count + ((width + 1) * 2) + ((height + 1) * 2));
    for(unsigned y=0; y<height+2; ++y) {
        for(unsigned x=0; x<width+2; ++x) {
            if(x==0 || x==width+1 || y==0 || y==height+1) {
                tiles.push_back(Tile(-1, -1, &terrains.at(TerrainType::MapEdge)));
            } else {
                tiles.push_back(Tile(x-1, y-1, &terrains.at(TerrainType::StoneFloor)));
            }
        }
    }
}

Tile& TileMap::get(const unsigned x, const unsigned y) {
    return tiles[((width+2) * (1+y)) + (1+x)];
}

Tile& TileMap::get(Tile &tile, const Direction direction) const {
    return *(&tile + tile_direction_offset.at(direction));
}

const Tile& TileMap::get(const Tile &tile, const Direction direction) const {
    return *(&tile + tile_direction_offset.at(direction));
}

const Terrain * const TileMap::get(const TerrainType terrain) {
    return &terrains.at(terrain);
}

void TileMap::generate(const unsigned width, const unsigned height) {
    init(width, height);
}

void TileMap::save() {
    /* TODO */
}

void TileMap::load() {
    /* TODO */
}

void TileMap::print() {
    std::stringstream ss;

    for(unsigned y=0; y<height; ++y) {
        for(unsigned x=0; x<width; ++x) {
            ss << get(x, y).terrain->ascii_char;
        }
        ss << '\n';
    }

    std::cout << ss.str() << '\n';
}

unsigned TileMap::manhattan_distance(const Tile &start, const Tile &end) const {
    return std::max(end.x, start.x) - std::min(end.x, start.x) + 
           std::max(end.y, start.y) - std::min(end.y, start.y);
}

unsigned TileMap::chebyshev_distance(const Tile &start, const Tile &end) const {
    return std::max(
        std::max(end.x, start.x) - std::min(end.x, start.x),
        std::max(end.y, start.y) - std::min(end.y, start.y)
    );
}

std::vector<Tile *> TileMap::get_path(
    Tile &start, Tile &end,
    bool(*tile_pathable)(const Tile &),
    const bool diagonal_movement) const
{
    const std::vector<TileMap::Direction> &neighbour_directions =
        diagonal_movement ? directions : cardinal_directions;

    std::map<Tile *, uint64_t> g_cost;
    std::map<Tile *, uint64_t> f_cost;

    std::unordered_set<Tile *> closed_set;
    std::unordered_set<Tile *> open_set = { &start };
    std::map<Tile *, Tile *> parent;

    g_cost[&start] = 0;
    f_cost[&start] = diagonal_movement ?
        chebyshev_distance(start, end) :
        manhattan_distance(start, end);

    while(!open_set.empty()) {
        Tile &current = **std::min_element(open_set.begin(), open_set.end(), [f_cost](Tile *a, Tile *b) {
            const uint64_t a_cost = get_with_default(f_cost, a, static_cast<uint64_t>(std::numeric_limits<uint64_t>::max()));
            const uint64_t b_cost = get_with_default(f_cost, b, static_cast<uint64_t>(std::numeric_limits<uint64_t>::max()));
            return a_cost < b_cost;
        });

        if(&current == &end) {
            std::vector<Tile *> path;
            Tile *cur_tile_ptr = &end;
            while(cur_tile_ptr) {
                path.push_back(cur_tile_ptr);
                cur_tile_ptr = get_with_default(parent, cur_tile_ptr, static_cast<Tile *>(nullptr));
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        open_set.erase(&current);
        closed_set.insert(&current);

        for(const auto direction : neighbour_directions) {
            Tile &neighbour = get(current, direction);

            if(neighbour.terrain->map_edge ||
                (closed_set.find(&neighbour) != closed_set.end()) ||
                ((!(*tile_pathable)(neighbour)) && (&neighbour != &end)))
            {
                continue;
            }

            if(open_set.find(&neighbour) == open_set.end()) {
                open_set.insert(&neighbour);
            }

            const uint64_t tmp_g_cost = 1 + get_with_default(g_cost, &current, static_cast<uint64_t>(std::numeric_limits<uint64_t>::max()));
            const uint64_t neighbour_g_cost = get_with_default(g_cost, &neighbour, static_cast<uint64_t>(std::numeric_limits<uint64_t>::max()));

            if(tmp_g_cost >= neighbour_g_cost) {
                continue;
            }

            parent[&neighbour] = &current;
            g_cost[&neighbour] = tmp_g_cost;
            f_cost[&neighbour] = tmp_g_cost + diagonal_movement ?
                chebyshev_distance(neighbour, end) :
                manhattan_distance(neighbour, end);
        }
    }

    return std::vector<Tile *>();
}
