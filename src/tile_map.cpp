#include "tile_map.hpp"

#include <sstream>
#include <iostream>
#include <limits>
#include <functional>
#include <unordered_set>
#include <set>
#include <cstdint>
#include <algorithm>

#include "tile_map.hpp"

template<template<typename, typename, typename...> typename C, typename K, typename V, typename... Args>
V get_with_default(const C<K, V, Args...> &m, K const &key, const V &default_val) {
    typename C<K, V, Args...>::const_iterator it = m.find(key);
    return it == m.end() ? default_val : it->second;
}

TileMap::TileMap(const unsigned width, const unsigned height) :
    id(map_count++)
{
    data = new TileMap::Data;
    data->width = width;
    data->height = height;
    data->tile_count = width * height;
}

TileMap::~TileMap() {
    /* Empty */
}

Tile& TileMap::get(const unsigned x, const unsigned y) const {
    return data->tiles[((data->width+2) * (1+y)) + (1+x)];
}

Tile& TileMap::get(Tile &tile, const Direction direction) const {
    const std::ptrdiff_t width = static_cast<long>(data->width + 2);
    std::ptrdiff_t offset;

    switch(direction) {
        case Direction::North:
            offset = -width;
            break;
        case Direction::NorthEast:
            offset = -width + 1;
            break;
        case Direction::East:
            offset = 1;
            break;
        case Direction::SouthEast:
            offset = width + 1;
            break;
        case Direction::South:
            offset = width;
            break;
        case Direction::SouthWest:
            offset = width - 1;
            break;
        case Direction::West:
            offset = -1;
            break;
        case Direction::NorthWest:
            offset = -width - 1;
            break;
    }
    return *(&tile + offset);
}

void TileMap::save() {
    /* TODO - save to file*/
    delete data;
}

void TileMap::load() {
    /* TODO - load from file */
}

void TileMap::print() const {
    std::stringstream ss;

    for(unsigned y=0; y<data->height; ++y) {
        for(unsigned x=0; x<data->width; ++x) {
            ss << get(x, y).terrain->ascii_char;
        }
        ss << '\n';
    }

    std::cout << ss.str() << '\n';
}

unsigned TileMap::manhattan_distance(const Tile &start, const Tile &end) const {
    return std::abs(static_cast<int>(start.x) - static_cast<int>(end.x)) +
        std::abs(static_cast<int>(start.y) - static_cast<int>(end.y));
}

unsigned TileMap::chebyshev_distance(const Tile &start, const Tile &end) const {
    return std::max(
        std::abs(static_cast<int>(start.x) - static_cast<int>(end.x)),
        std::abs(static_cast<int>(start.y) - static_cast<int>(end.y))
    );
}

std::vector<Tile *> TileMap::get_path(
    Tile &start, Tile &end,
    bool(*tile_pathable)(const Tile &),
    const bool diagonal_movement) const
{
    constexpr static const uint64_t default_cost = std::numeric_limits<uint64_t>::max();

    const std::vector<Direction> &neighbour_directions =
        diagonal_movement ? directions : cardinal_directions;

    std::unordered_map<Tile *, uint64_t> g_cost;
    std::unordered_map<Tile *, uint64_t> f_cost;

    const auto f_cost_comp = [&f_cost](Tile *a, Tile *b) {
        const uint64_t a_cost = get_with_default(f_cost, a, default_cost);
        const uint64_t b_cost = get_with_default(f_cost, b, default_cost);
        return a_cost > b_cost;
    };

    std::unordered_set<Tile *> closed_set;
    std::set<Tile *, decltype(f_cost_comp)> open_set(f_cost_comp);
    open_set.insert(&start);
    std::unordered_map<Tile *, Tile *> parent;

    g_cost[&start] = 0;
    f_cost[&start] = diagonal_movement ?
        chebyshev_distance(start, end) :
        manhattan_distance(start, end);

    while(!open_set.empty()) {
        const auto current_it = --open_set.end();
        Tile &current = **current_it;

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

        open_set.erase(current_it);
        closed_set.insert(&current);

        for(const auto direction : neighbour_directions) {
            Tile &neighbour = get(current, direction);

            if(neighbour.terrain->map_edge ||
                (closed_set.find(&neighbour) != closed_set.end()) ||
                ((!(*tile_pathable)(neighbour)) && (&neighbour != &end)))
            {
                continue;
            }

            open_set.insert(&neighbour);

            const uint64_t tmp_g_cost = get_with_default(g_cost, &current, default_cost) + neighbour.terrain->path_cost;
            const uint64_t neighbour_g_cost = get_with_default(g_cost, &neighbour, default_cost);

            if(neighbour_g_cost < tmp_g_cost) {
                continue;
            }

            parent[&neighbour] = &current;
            g_cost[&neighbour] = tmp_g_cost;
            f_cost[&neighbour] = tmp_g_cost + (diagonal_movement ?
                chebyshev_distance(neighbour, end) :
                manhattan_distance(neighbour, end)
            );
        }
    }

    return std::vector<Tile *>();
}
