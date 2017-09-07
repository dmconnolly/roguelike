#include "tile.hpp"

Tile::Tile() {
	/* Empty */
}

Tile::Tile(const Tile &rhs) {
	/* Empty */
}

Tile::Tile(Tile &&rhs) {
	// data.swap(rhs.data);
}

Tile& Tile::operator=(const Tile &rhs) {
	// data = rhs.data;
	return *this;
}

Tile& Tile::operator=(Tile &&rhs) {
	// data.swap(rhs.data);
	return *this;
}
