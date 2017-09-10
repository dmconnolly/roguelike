#pragma once
#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "tile.hpp"

class Terrain {
public:
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

    const bool pathable;
	const bool pathable_flying;
	const char ascii_char;
	const bool map_edge;
};

#endif /* TILE_TYPE_HPP */
