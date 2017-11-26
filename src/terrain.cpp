#include "terrain.hpp"

const Terrain * const Terrain::get(const Terrain::Type terrain) {
    return &all.at(terrain);
}

const std::map<const Terrain::Type, const Terrain> Terrain::all = {
    { Terrain::Type::MapEdge, Terrain(Terrain::Type::MapEdge) },
    { Terrain::Type::StoneWall, Terrain(Terrain::Type::StoneWall) },
    { Terrain::Type::StoneFloor, Terrain(Terrain::Type::StoneFloor) }
};
