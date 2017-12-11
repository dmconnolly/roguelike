#include "terrain.hpp"

const Terrain * const Terrain::get(const Terrain::Type terrain) {
    return &all.at(terrain);
}

const std::map<const Terrain::Type, const Terrain> Terrain::all = {
    { Terrain::Type::MapEdge, Terrain(Terrain::Type::MapEdge) },
    { Terrain::Type::StoneWall, Terrain(Terrain::Type::StoneWall) },
    { Terrain::Type::HardStoneWall, Terrain(Terrain::Type::HardStoneWall) },
    { Terrain::Type::StoneFloor, Terrain(Terrain::Type::StoneFloor) },
    { Terrain::Type::StairsUp, Terrain(Terrain::Type::StairsUp) },
    { Terrain::Type::StairsDown, Terrain(Terrain::Type::StairsDown) }
};
