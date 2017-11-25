#pragma once
#ifndef TILE_MAP_BASE_HPP
#define TILE_MAP_BASE_HPP

#include <atomic>

class TileMapBase {
protected:
    static std::atomic<unsigned> map_count;
};

#endif /* TILE_MAP_BASE_HPP */
