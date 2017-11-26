#pragma once
#ifndef FEATURE_HPP
#define FEATURE_HPP

#include <unordered_set>

#include "tile.hpp"

class Feature {
public:
    /* Constructor */
    Feature() = default;

    /* Destructor */
    ~Feature() = default;

    /* Delete copy constructors */
    Feature(const Feature &rhs) = delete;
    Feature(Feature &&rhs) = delete;

    /* Delete assignment operators */
    Feature& operator=(const Feature &rhs) = delete;
    Feature& operator=(Feature &&rhs) = delete;

private:
    std::unordered_set<Tile *> tiles;
    std::unordered_set<Tile *> centre_tiles;
    std::unordered_set<Tile *> edge_tiles;
    std::unordered_set<Tile *> entrance_tiles;
};

#endif /* FEATURE_HPP */
