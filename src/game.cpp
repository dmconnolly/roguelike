#include "game.hpp"
#include "map_generator.hpp"

Game::Game() {
    /* Empty */
}

void Game::start() {
    current_map = new TileMap(100, 50);
    MapGenerator map_gen(*current_map);
    map_gen.build();

    current_map->print();

    //std::vector<Tile *> path;

    //Tile &start = current_map->get(1, 1);
    //Tile &end = current_map->get(98, 48);

    //path = current_map->get_path(start, end, [](const Tile &tile) {
    //    return true;
    //}, false, true);

    //for(auto *tile : path) {
    //    tile->terrain = Terrain::get(Terrain::Type::MapEdge);
    //}

    //current_map->print();
}

void Game::step() {
    /* TODO */
}
