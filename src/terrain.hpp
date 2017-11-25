#pragma once
#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <map>

class Terrain {
public:
    const bool pathable;
    const bool pathable_flying;
    const char ascii_char;
    const bool map_edge;

    enum class Type : unsigned char {
        MapEdge,
        StoneWall,
        StoneFloor
    };

    constexpr Terrain(
        const bool pathable,
        const bool pathable_flying,
        const char ascii_char,
        const bool map_edge) :
    pathable(pathable),
    pathable_flying(pathable_flying),
    ascii_char(ascii_char),
    map_edge(map_edge)
    {
        /* Empty */
    }

    ~Terrain() = default;
    Terrain& operator=(const Terrain&) = delete;
    static const Terrain * const get(const Terrain::Type terrain);

    static constexpr const Terrain Terrain::create(const Terrain::Type type) {
        bool pathable = false;
        bool pathable_flying = false;
        char ascii_char = '?';
        bool map_edge = false;

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

        return Terrain(
            pathable,
            pathable_flying,
            ascii_char,
            map_edge
        );
    }
};

static const std::map<const Terrain::Type, const Terrain> terrains = {
    { Terrain::Type::MapEdge, Terrain::create(Terrain::Type::MapEdge) },
    { Terrain::Type::StoneWall, Terrain::create(Terrain::Type::StoneWall) },
    { Terrain::Type::StoneFloor, Terrain::create(Terrain::Type::StoneFloor) }
};

#endif /* TILE_TYPE_HPP */
