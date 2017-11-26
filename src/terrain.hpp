#pragma once
#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <map>

class Terrain {
public:
    bool pathable;
    bool pathable_flying;
    char ascii_char;
    bool map_edge;

    enum class Type : unsigned char {
        MapEdge,
        StoneWall,
        StoneFloor
    };

    Terrain(const Terrain::Type type) {
        pathable = false;
        pathable_flying = false;
        ascii_char = '?';
        map_edge = false;

        switch(type) {
            case Terrain::Type::MapEdge:
                pathable = false;
                pathable_flying = false;
                ascii_char = 'x';
                map_edge = true;
                break;
            case Terrain::Type::StoneWall:
                pathable = false;
                pathable_flying = false;
                ascii_char = '+';
                break;
            case Terrain::Type::StoneFloor:
                pathable = true;
                pathable_flying = true;
                ascii_char = '.';
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
