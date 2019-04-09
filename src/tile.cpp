#include "tile.hpp"

Tile::Tile(const unsigned x, const unsigned y, const Terrain *terrain) :
    x(x),
    y(y),
    terrain(terrain),
    discovered(false)
{
    // Empty
}

Tile::Tile(const Tile &rhs) :
    discovered(rhs.discovered),
    x(rhs.x),
    y(rhs.y),
    terrain(rhs.terrain)
{
    // Empty
}

Tile::Tile(Tile &&rhs) :
    discovered(rhs.discovered),
    x(rhs.x),
    y(rhs.y),
    terrain(rhs.terrain)
{
    // Empty
}
