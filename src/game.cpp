#include "game.hpp"
#include "map_generator.hpp"

Game::Game() {
    /* Empty */
}
#include <chrono>
#include <iostream>
void Game::start() {
    current_map = new TileMap(100, 50);
    MapGenerator map_gen(*current_map);
    map_gen.build();

    current_map->print();

    std::vector<Tile *> path;

    const unsigned loop_count = 100;
    long long total = 0;
    Tile &start = current_map->get(0, 0);
    Tile &end = current_map->get(99, 49);

    for(unsigned i=0; i<loop_count; ++i) {
        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        path = current_map->get_path(start, end, [](const Tile &tile) {
            return true;
        }, false);

        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        total += std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    }

    for(auto *tile : path) {
        tile->terrain = Terrain::get(Terrain::Type::MapEdge);
    }

    current_map->print();

    std::cout << total / loop_count << " ms\n";
}

void Game::step() {
    /* TODO */
}
