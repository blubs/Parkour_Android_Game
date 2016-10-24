//
// Created by F1 on 8/22/2016.
//

#ifndef PARKOUR_TILE_HPP
#define PARKOUR_TILE_HPP


#include "../engine/graphics/Static_Model.hpp"
#include "../game/Maneuver.hpp"
#include "../game/game_defs.hpp"
#include "../engine/misc.hpp"

class Collision_Map
{
public:
	char voxel[TILE_VOXEL_DIMS][TILE_VOXEL_DIMS];
	Collision_Map();
	~Collision_Map();

	char get_vox_at(int x, int y);
};

class Grid_Tile
{
public:
	//TODO: store maneuver data
	//TODO: store traversal data
	Maneuver** maneuvers;
	int maneuver_count;

	Traversal** traversals;
	int traversal_count;

	Static_Model* model;
	Collision_Map* coll_map;

	Grid_Tile(int man_count, int trav_count);
	~Grid_Tile();
};

#endif //PARKOUR_TILE_HPP
