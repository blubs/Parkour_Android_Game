//
// Created by F1 on 8/22/2016.
//

#ifndef PARKOUR_TILE_HPP
#define PARKOUR_TILE_HPP


#include "../engine/graphics/Static_Model.hpp"

//Size of tiles (6 units x 6 units x 6 units)
#define TILE_SIZE 3.5f
#define WINDOW_TILE_SIZE 7.0f
#define GRID_SIZE 0.5f

#define BUILDING_MAX_WIDTH 60
#define BUILDING_MAX_LENGTH 120

//2 voxels per meter, 3.5m x 3.5m tile = 7v x 7v voxel map
#define TILE_VOXEL_DIMS 7
#define TILE_VOXELS 49

class Collision_Map
{
public:
	//are we going to allow for arbitrarily sized tiles?
	static const char VOX_EMPTY = 0;
	static const char VOX_SOLID = 1;
	//static const char VOX_DOORWAY = 2;
	//...etc

	char tile[TILE_VOXEL_DIMS][TILE_VOXEL_DIMS];
	Collision_Map();
	~Collision_Map();

	char get_vox_at(int x, int y);
};

class Grid_Tile
{
public:
	//TODO: store maneuver data
	//TODO: store traversal data
	Static_Model* model;
	Collision_Map* coll_map;

	Grid_Tile();
	~Grid_Tile();
};

#endif //PARKOUR_TILE_HPP
