//
// Created by F1 on 8/22/2016.
//

#include "Grid_Tile.hpp"

Collision_Map::Collision_Map()
{
	tile[0][0] = tile[0][1] = tile[0][2] = tile[0][3] = tile[0][4] = tile[0][5] =
	tile[1][0] = tile[1][1] = tile[1][2] = tile[1][3] = tile[1][4] = tile[1][5] =
	tile[2][0] = tile[2][1] = tile[2][2] = tile[2][3] = tile[2][4] = tile[2][5] =
	tile[3][0] = tile[3][1] = tile[3][2] = tile[3][3] = tile[3][4] = tile[3][5] =
	tile[4][0] = tile[4][1] = tile[4][2] = tile[4][3] = tile[4][4] = tile[4][5] =
	tile[5][0] = tile[5][1] = tile[5][2] = tile[5][3] = tile[5][4] = tile[5][5] = VOX_EMPTY;
}
Collision_Map::~Collision_Map()
{
}

char Collision_Map::get_vox_at(int x, int y)
{
	return tile[x][y];
}

Grid_Tile::Grid_Tile()
{
	//model = new Static_Model("filename");
	//have to instantiate at load
	coll_map = new Collision_Map();
}
Grid_Tile::~Grid_Tile()
{
	//delete model on unload
	delete coll_map;
}