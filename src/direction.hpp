#pragma once
#ifndef DIRECTION_HPP
#define DIRECTION_HPP

#include <vector>

enum class Direction : unsigned char {
    North, NorthEast,
    East, SouthEast,
    South, SouthWest,
    West, NorthWest
};

static const std::vector<Direction> directions = {
    Direction::North, Direction::NorthEast,
    Direction::East, Direction::SouthEast,
    Direction::South, Direction::SouthWest,
    Direction::West, Direction::NorthWest
};

static const std::vector<Direction> cardinal_directions = {
    Direction::North, Direction::East,
    Direction::South, Direction::West
};

static const std::vector<Direction> intercardinal_directions = {
    Direction::NorthEast, Direction::SouthEast,
    Direction::SouthWest, Direction::NorthWest
};

#endif // DIRECTION_HPP
