#pragma once
#ifndef FEATURE_HPP
#define FEATURE_HPP

#include <vector>

#include "tile.hpp"

class Feature {
public:
    enum class Type : unsigned char {
        EntranceRoom,
        ExitRoom,
        Room,
        Corridor,
        None
    };

    std::vector<Tile *> tiles;
    std::vector<Tile *> centre_tiles;
    std::vector<Tile *> edge_tiles;
    std::vector<Tile *> entrance_tiles;

    /* Constructor */
    Feature::Feature(const Feature::Type type=Feature::Type::None);

    /* Default destructor */
    ~Feature() = default;

    /* Delete copy constructor */
    Feature(const Feature &rhs) = delete;
    /* Allow move though */
    Feature(Feature &&rhs) = default;

    /* Delete assignment operators */
    Feature& operator=(const Feature &rhs) = delete;
    Feature& operator=(Feature &&rhs) = delete;

private:
    Feature::Type type;
};

#endif /* FEATURE_HPP */
