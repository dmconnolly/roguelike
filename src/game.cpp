#include "game.hpp"

Game::Game() {
	/* Empty */
}
#include <iostream>
void Game::start() {
	tile_map.generate(20, 10);
	tile_map.print();

	Tile &start = tile_map.get(1, 1);
	Tile &end = tile_map.get(5, 8);

	std::vector<Tile *> path = tile_map.get_path(start, end, [](const Tile &tile) {
		return !tile.terrain->map_edge;
	}, false);

	for(auto tile_ptr : path) {
		tile_ptr->terrain = TileMap::get(TileMap::TerrainType::MapEdge);
	}

	tile_map.print();
}

void Game::step() {
	/* TODO */
}
