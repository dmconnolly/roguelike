#pragma once
#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <map>
#include <limits>

class Terrain {
public:
    bool pathable;
    bool pathable_flying;
    char ascii_char;
    bool map_edge;
    unsigned path_cost;

    enum class Type : unsigned char {
        MapEdge,
        StoneWall,
        HardStoneWall,
        StoneFloor,
        StairsUp,
        StairsDown
    };

    Terrain(const Terrain::Type type) {
        pathable = false;
        pathable_flying = false;
        ascii_char = '?';
        map_edge = false;
        path_cost = 5;

        switch(type) {
            case Terrain::Type::MapEdge:
                pathable = false;
                pathable_flying = false;
                ascii_char = 'x';
                map_edge = true;
                path_cost = std::numeric_limits<unsigned>::max();
                break;
            case Terrain::Type::StoneWall:
                pathable = false;
                pathable_flying = false;
                ascii_char = '+';
                path_cost = 7;
                break;
            case Terrain::Type::HardStoneWall:
                pathable = false;
                pathable_flying = false;
                ascii_char = '#';
                path_cost = 1200;
                break;
            case Terrain::Type::StoneFloor:
                pathable = true;
                pathable_flying = true;
                ascii_char = '.';
                path_cost = 5;
                break;
            case Terrain::Type::StairsUp:
                pathable = true;
                pathable_flying = true;
                ascii_char = '<';
                path_cost = 6;
                break;
            case Terrain::Type::StairsDown:
                pathable = true;
                pathable_flying = true;
                ascii_char = '>';
                path_cost = 6;
                break;
        };
    }

    ~Terrain() = default;
    Terrain& operator=(const Terrain&) = delete;

    static const Terrain * const get(const Terrain::Type terrain);

private:
    static const std::map<const Terrain::Type, const Terrain> all;
};

#endif /* TERRAIN_HPP */
