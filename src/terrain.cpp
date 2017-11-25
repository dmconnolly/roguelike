#include "terrain.hpp"

const Terrain * const Terrain::get(const Terrain::Type terrain) {
    return &terrains.at(terrain);
}
