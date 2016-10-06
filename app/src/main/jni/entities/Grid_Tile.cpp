//
// Created by F1 on 8/22/2016.
//

#include "Grid_Tile.hpp"

Collision_Map::Collision_Map()
{
	voxel[0][0] = voxel[0][1] = voxel[0][2] = voxel[0][3] = voxel[0][4] = voxel[0][5] = voxel[0][6] =
	voxel[1][0] = voxel[1][1] = voxel[1][2] = voxel[1][3] = voxel[1][4] = voxel[1][5] = voxel[1][6] =
	voxel[2][0] = voxel[2][1] = voxel[2][2] = voxel[2][3] = voxel[2][4] = voxel[2][5] = voxel[2][6] =
	voxel[3][0] = voxel[3][1] = voxel[3][2] = voxel[3][3] = voxel[3][4] = voxel[3][5] = voxel[3][6] =
	voxel[4][0] = voxel[4][1] = voxel[4][2] = voxel[4][3] = voxel[4][4] = voxel[4][5] = voxel[4][6] =
	voxel[5][0] = voxel[5][1] = voxel[5][2] = voxel[5][3] = voxel[5][4] = voxel[5][5] = voxel[5][6] =
	voxel[6][0] = voxel[6][1] = voxel[6][2] = voxel[6][3] = voxel[6][4] = voxel[6][5] = voxel[6][6] =  VOX_EMPTY;
}
Collision_Map::~Collision_Map()
{
}

char Collision_Map::get_vox_at(int x, int y)
{
	return voxel[x][y];
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