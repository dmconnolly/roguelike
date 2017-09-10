#include "tile.hpp"

Tile::Tile(const unsigned x, const unsigned y, const Terrain *terrain) :
	x(x),
	y(y),
    terrain(terrain)
{
	/* Empty */
}

Tile::Tile(const Tile &rhs) :
	x(rhs.x),
	y(rhs.y),
	terrain(rhs.terrain)
{
	/* Empty */
}

Tile::Tile(Tile &&rhs) :
	x(rhs.x),
	y(rhs.y),
	terrain(rhs.terrain)
{
	/* Empty */
}

Tile& Tile::operator=(const Tile &rhs) {
	terrain = rhs.terrain;
	return *this;
}

Tile& Tile::operator=(Tile &&rhs) {
	terrain = rhs.terrain;
	return *this;
}
