#pragma once
#ifndef ROOM_HPP
#define ROOM_HPP

#include <vector>

#include "tile.hpp"

class Room {
public:
    enum class Type : unsigned char {
        EntranceRoom,
        ExitRoom,
        Room,
        Corridor,
        None
    };

    Room::Type type;
    std::vector<Tile *> tiles;
    std::vector<Tile *> centre_tiles;
    std::vector<Tile *> edge_tiles;
    std::vector<Tile *> connection_tiles;

    /* Constructor */
    Room::Room(const Room::Type type=Room::Type::None);

    /* Default destructor */
    ~Room() = default;

    /* Delete copy constructor */
    Room(const Room &rhs) = delete;
    /* Allow move though */
    Room(Room &&rhs) = default;

    /* Delete assignment operators */
    Room& operator=(const Room &rhs) = delete;
    Room& operator=(Room &&rhs) = delete;
};

#endif /* ROOM_HPP */
