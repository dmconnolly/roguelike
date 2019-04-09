#pragma once
#ifndef ROOM_HPP
#define ROOM_HPP

#include <unordered_set>

#include "tile.hpp"

class Room {
public:
    std::string name;
    unsigned width;
    unsigned height;
    unsigned char ascii;
    std::vector<Tile *> tiles;
    std::vector<Tile *> centre_tiles;
    std::vector<Tile *> edge_tiles;
    std::vector<Tile *> connection_tiles;

    // Constructor
    Room::Room() = default;

    // Default destructor
    ~Room() = default;

    // Delete copy constructors
    Room(const Room &rhs) = delete;
    Room(Room &&rhs) = default;

    // Delete assignment operators
    Room& operator=(const Room &rhs) = delete;
    Room& operator=(Room &&rhs) = delete;
};

#endif // ROOM_HPP
