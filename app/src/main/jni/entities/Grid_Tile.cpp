//
// Created by F1 on 8/22/2016.
//

#include "Grid_Tile.hpp"

Collision_Map::Collision_Map()
{
	//Defaulting voxels to empty
	voxel[0][0] = voxel[0][1] = voxel[0][2] = voxel[0][3] = voxel[0][4] = voxel[0][5] = voxel[0][6] =
	voxel[1][0] = voxel[1][1] = voxel[1][2] = voxel[1][3] = voxel[1][4] = voxel[1][5] = voxel[1][6] =
	voxel[2][0] = voxel[2][1] = voxel[2][2] = voxel[2][3] = voxel[2][4] = voxel[2][5] = voxel[2][6] =
	voxel[3][0] = voxel[3][1] = voxel[3][2] = voxel[3][3] = voxel[3][4] = voxel[3][5] = voxel[3][6] =
	voxel[4][0] = voxel[4][1] = voxel[4][2] = voxel[4][3] = voxel[4][4] = voxel[4][5] = voxel[4][6] =
	voxel[5][0] = voxel[5][1] = voxel[5][2] = voxel[5][3] = voxel[5][4] = voxel[5][5] = voxel[5][6] =
	voxel[6][0] = voxel[6][1] = voxel[6][2] = voxel[6][3] = voxel[6][4] = voxel[6][5] = voxel[6][6] =  CLIP_EMPTY;

	//Defaulting all voxel shapes to boxes
	voxel_shape[0][0] = voxel_shape[0][1] = voxel_shape[0][2] = voxel_shape[0][3] = voxel_shape[0][4] =
	voxel_shape[0][5] = voxel_shape[0][6] = voxel_shape[1][0] = voxel_shape[1][1] = voxel_shape[1][2] =
	voxel_shape[1][3] = voxel_shape[1][4] = voxel_shape[1][5] = voxel_shape[1][6] = voxel_shape[2][0] =
	voxel_shape[2][1] = voxel_shape[2][2] = voxel_shape[2][3] = voxel_shape[2][4] = voxel_shape[2][5] =
	voxel_shape[2][6] = voxel_shape[3][0] = voxel_shape[3][1] = voxel_shape[3][2] = voxel_shape[3][3] =
	voxel_shape[3][4] = voxel_shape[3][5] = voxel_shape[3][6] = voxel_shape[4][0] = voxel_shape[4][1] =
	voxel_shape[4][2] = voxel_shape[4][3] = voxel_shape[4][4] = voxel_shape[4][5] = voxel_shape[4][6] =
	voxel_shape[5][0] = voxel_shape[5][1] = voxel_shape[5][2] = voxel_shape[5][3] = voxel_shape[5][4] =
	voxel_shape[5][5] = voxel_shape[5][6] = voxel_shape[6][0] = voxel_shape[6][1] = voxel_shape[6][2] =
	voxel_shape[6][3] = voxel_shape[6][4] = voxel_shape[6][5] = voxel_shape[6][6] =  CLIP_SHAPE_BOX;
}
Collision_Map::~Collision_Map()
{
}

char Collision_Map::get_vox_at(int x, int y)
{
	return voxel[x][y];
}

char Collision_Map::get_vox_shape_at(int x, int y)
{
	return voxel_shape[x][y];
}


char Collision_Map::get_vox_at(int x, int y, float vpos_x, float vpos_y)
{
	switch(voxel_shape[x][y])
	{
		default:
		case CLIP_SHAPE_BOX:
			return voxel[x][y];

		//Solid area is the area under the line y=x
		case CLIP_SHAPE_LT_POS:
			return (y <= x) ? voxel[x][y] : (char)CLIP_EMPTY;

		//Solid area is the area above the line y=x
		case CLIP_SHAPE_GT_POS:
			return (y >= x) ? voxel[x][y] : (char)CLIP_EMPTY;

		//Solid area is the area under the line y=0.5 - x
		case CLIP_SHAPE_LT_NEG:
			return (y <= (0.5f - x)) ? voxel[x][y] : (char)CLIP_EMPTY;

		//Solid area is the area above the line y=(x-0.25) + 0.25
		case CLIP_SHAPE_GT_NEG:
			return (y >= (0.5f - x)) ? voxel[x][y] : (char)CLIP_EMPTY;

		//Solid area is the area under the line y=abs(x-0.25) + 0.25
		case CLIP_SHAPE_GT_ABS:
			return (y <= (fabsf(x-0.25f) + 0.25f)) ? voxel[x][y] : (char)CLIP_EMPTY;

		//Solid area is the area above the line y=-abs(x-0.25) + 0.25
		case CLIP_SHAPE_LT_ABS:
			return (y >= (-fabsf(x-0.25f) + 0.25f)) ? voxel[x][y] : (char)CLIP_EMPTY;

		//Solid area is the area above the line y=x-0.15 and under the line y=x+0.15
		case CLIP_SHAPE_IN_WALL_POS:
			return ( (y >= x - 0.15f) && (y <= x + 0.15f) ) ? voxel[x][y] : (char)CLIP_EMPTY;

		//Solid area is the area above the line y=-x+0.35 and under the line y=-x+0.65
		case CLIP_SHAPE_IN_WALL_NEG:
			return ( (y >= -x + 0.35f) && (y <= -x + 0.65f) ) ? voxel[x][y] : (char)CLIP_EMPTY;
	}
}


Grid_Tile::Grid_Tile(int man_count, int trav_count)
{
	//model = new Static_Model("filename");
	//have to instantiate at load
	coll_map = new Collision_Map();

	maneuver_count = man_count;
	traversal_count = trav_count;
	maneuvers = new Maneuver*[man_count];
	traversals = new Traversal*[trav_count];
}
Grid_Tile::~Grid_Tile()
{
	//delete model on unload
	delete coll_map;

	for(int i = 0; i < maneuver_count; i++)
	{
		delete maneuvers[i];
	}
	for(int i = 0; i < traversal_count; i++)
	{
		delete traversals[i];
	}

	delete[] maneuvers;
	delete[] traversals;
}