//
// Created by F1 on 8/22/2016.
//

#ifndef PARKOUR_TILE_HPP
#define PARKOUR_TILE_HPP


#include "../engine/graphics/Static_Model.hpp"

//Size of tiles (6 units x 6 units x 6 units)
#define GRIDSIZE 3
#define WINDOWGRIDSIZE 6

#define BUILDING_MAX_WIDTH 60
#define BUILDING_MAX_LENGTH 120



class Collision_Map
{
public:
	//are we going to allow for arbitrarily sized tiles?
	static const char VOX_EMPTY = 0;
	static const char VOX_SOLID = 1;
	//static const char VOX_DOORWAY = 2;
	//...etc

	//2 voxels per meter, 3m x 3m tile = 6v x 6v voxel map
	char tile[6][6];
	Collision_Map()
	{
		tile[0][0] = tile[0][1] = tile[0][2] = tile[0][3] = tile[0][4] = tile[0][5] =
		tile[1][0] = tile[1][1] = tile[1][2] = tile[1][3] = tile[1][4] = tile[1][5] =
		tile[2][0] = tile[2][1] = tile[2][2] = tile[2][3] = tile[2][4] = tile[2][5] =
		tile[3][0] = tile[3][1] = tile[3][2] = tile[3][3] = tile[3][4] = tile[3][5] =
		tile[4][0] = tile[4][1] = tile[4][2] = tile[4][3] = tile[4][4] = tile[4][5] =
		tile[5][0] = tile[5][1] = tile[5][2] = tile[5][3] = tile[5][4] = tile[5][5] = VOX_EMPTY;
	}
	~Collision_Map()
	{
	}

	char get_vox_at(int x, int y)
	{
		return tile[x][y];
	}
};

class Grid_Tile
{
public:
	//TODO: store maneuver data
	//TODO: store traversal data
	Static_Model* model;
	Collision_Map* coll_map;

	Grid_Tile()
	{
		//model = new Static_Model("filename");
		//have to instantiate at load
		coll_map = new Collision_Map();
	}
	~Grid_Tile()
	{
		//delete model on unload
		delete coll_map;
	}
};

#endif //PARKOUR_TILE_HPP
