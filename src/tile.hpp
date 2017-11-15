#pragma once
#ifndef TILE_HPP
#define TILE_HPP

#include <string>

#include "terrain.hpp"

class Tile {
public:
    const bool discovered;
    const unsigned x;
    const unsigned y;
    const Terrain *terrain;

    /* Constructors */
    Tile(const unsigned x, const unsigned y, const Terrain *terrain=nullptr);
    Tile(const Tile &rhs);
    Tile(Tile &&rhs);
    ~Tile() = default;

    /* Operator overloads */
    Tile& operator=(const Tile &rhs) = delete;
    Tile& operator=(Tile &&rhs) = delete;
};

#endif /* TILE_HPP */
