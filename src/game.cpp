#include "game.hpp"

Game::Game() {
    /* Empty */
}

void Game::start() {
    current_map = new TileMap(map_id++, 20, 10);
    current_map->print();

    Tile &start = current_map->get(1, 1);
    Tile &end = current_map->get(12, 8);

    std::vector<Tile *> path = current_map->get_path(start, end, [](const Tile &tile) {
        return !tile.terrain->map_edge;
    }, false);

    for(auto tile_ptr : path) {
        tile_ptr->terrain = TileMap::get(TileMap::TerrainType::MapEdge);
    }

    current_map->print();
}

void Game::step() {
    /* TODO */
}
