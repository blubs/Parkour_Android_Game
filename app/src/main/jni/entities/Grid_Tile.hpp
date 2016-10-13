//
// Created by F1 on 8/22/2016.
//

#ifndef PARKOUR_TILE_HPP
#define PARKOUR_TILE_HPP


#include "../engine/graphics/Static_Model.hpp"
#include "../game/Maneuver.hpp"
#include "../game/game_defs.hpp"

class Collision_Map
{
public:
	//are we going to allow for arbitrarily sized tiles?
	static const char VOX_EMPTY = 0;
	static const char VOX_SOLID = 1;
	//static const char VOX_DOORWAY = 2;
	//...etc

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
