//
// Created by F1 on 8/22/2016.
//

#ifndef PARKOUR_FLOOR_HPP
#define PARKOUR_FLOOR_HPP

#include "../engine/math/math.hpp"
#include "../engine/Game_Object.hpp"
#include "Grid_Tile.hpp"
#include "../game/Global_Tiles.hpp"

class Floor : Entity
{
public:
	//height of the floor's ground level
	float altitude;

	static const int MAX_WIDTH = BUILDING_MAX_WIDTH;
	static const int MAX_LENGTH = BUILDING_MAX_LENGTH;

	//Width/length in tiles
	int width;
	int length;

	//center near bottom of floor
	Vec3 global_pos;
	Vec3 global_mins;
	Vec3 global_maxs;

	//Type index of tile
	int tile_type[MAX_WIDTH][MAX_LENGTH];
	//Variant index of tile
	int tile_variant[MAX_WIDTH][MAX_LENGTH];

	//What tile set are we using?
	int interior_style;
	//What material are we using?
	int interior_variant;

	//For convenience/speed, we're going to hold an array of pointers to models and collision maps
	Collision_Map* tile_coll_map[MAX_WIDTH][MAX_LENGTH];
	Static_Model* tile_model[MAX_WIDTH][MAX_LENGTH];

	Floor()
	{
		global_pos = Vec3(0,0,0);
		altitude = 0;
	}
	~Floor()
	{
	}

	void generate(Vec3 p, int floor_num, Vec3 mins, Vec3 maxs)
	{
		altitude = p.z + floor_num*(WINDOW_TILE_SIZE);
		global_pos = p + Vec3(0,0,floor_num*WINDOW_TILE_SIZE);
		global_mins = mins;
		global_maxs = maxs;
		global_mins.z = global_maxs.z = altitude;
		width = (int)(global_maxs.x - global_mins.x)/TILE_SIZE;
		length = (int)(global_maxs.y - global_mins.y)/TILE_SIZE;

		//For now, populate floor with empty tiles.
		for(int i = 0; i < width; i++)
		{
			for(int j = 0; j < length; j++)
			{
				int ttype = TILE_TYPE_EMPT;

				//Setting a few of the tiles as something else
				//FIXME: the following logic hand picks a few tiles to place them at specific floor indices
				if(j == 3)
				{
					if(i == 2)
					{
						ttype = TILE_TYPE_SOLD;
					}
					if(i == 4)
					{
						//FIXME: generic 2 is not a type, replace ths
						//test vent
						ttype = 2;
					}
					if(i == 6)
					{
						//test vent 2
						ttype = 3;
					}
				}
				//FIXME: end temp section
				tile_type[i][j] = ttype;
				//TODO: get random variant number of this type
				tile_variant[i][j] = 0;
				//Setting references to models and collision maps
				tile_coll_map[i][j] = Global_Tiles::instance->test_tiles[ttype]->coll_map;
				tile_model[i][j] = Global_Tiles::instance->test_tiles[ttype]->model;
			}
		}
	}


	int render(Mat4 vp)
	{
		//how do we get the material?
		//Need to iterate through all tiles in this floor and draw them
		//Starting from frontmost tile, render it and all other tiles that use the same model
		//Then move onto the next unrendered tile
		//TODO: how will we store tile type in the floors?
		Global_Tiles::instance->style[0]->variants[0]->bind_variant();

		Material* mat = Global_Tiles::instance->style[0]->variants[0]->mat;

		Mat4 m;
		Mat4 world_trans = Mat4::TRANSLATE(global_mins);

		//Quick unoptimized test for rendering
		for(int i = 0; i < width; i++)
		{
			for(int j = 0; j < length; j++)
			{
				tile_model[i][j]->bind_mesh_data(mat);

				m = world_trans * Mat4::TRANSLATE(Vec3(i*TILE_SIZE,j*TILE_SIZE,0));

				Mat4 mvp = vp * m;
				mat->bind_value(Shader::PARAM_MVP_MATRIX, (void*) mvp.m);

				Mat3 m_it = m.inverted_then_transposed().get_mat3();
				mat->bind_value(Shader::PARAM_M_IT_MATRIX, (void*) m_it.m);

				tile_model[i][j]->render_without_bind();
			}
		}
	}

	void clear()
	{
		altitude = 0;
		width = length = 0;
		global_mins = Vec3::ZERO();
		global_maxs = Vec3::ZERO();
	}

	char is_solid_at(Vec3 p)
	{
		//position given is in floor space, 0,0 being near left corner
		//get tile indices for the position
		if(is_x_out_of_bounds(p) || is_y_out_of_bounds(p))
			return Collision_Map::VOX_SOLID;

		Vec3 vox_p = Vec3(fmodf(p.x,TILE_SIZE),fmodf(p.y,TILE_SIZE),0);

		int tile_x = (int) floorf((p.x - vox_p.x)/TILE_SIZE);
		int tile_y = (int) floorf((p.y - vox_p.y)/TILE_SIZE);

		if(tile_x < 0 || tile_y < 0 || tile_x >= width || tile_y >= length)
		{
			LOGE("Warning: tried reaching out of bounds tile: (floor dims: (%d x %d), index: (%d x %d))",width,length,tile_x,tile_y);
			return Collision_Map::VOX_EMPTY;
		}

		int vox_x = (int) (floorf(vox_p.x/GRID_SIZE));
		int vox_y = (int) (floorf(vox_p.y/GRID_SIZE));

		if(vox_x < 0 || vox_y < 0 || vox_x >= TILE_VOXEL_DIMS || vox_y >= TILE_VOXEL_DIMS)
		{
			LOGE("Warning: tried reaching out of bounds voxel: (index: (%d x %d))",vox_x,vox_y);
			return Collision_Map::VOX_EMPTY;
		}

		char rank = tile_coll_map[tile_x][tile_y]->get_vox_at(vox_x,vox_y);
		LOGE("Tile[%d][%d], Voxel[%d][%d] = %d",tile_x,tile_y,vox_x,vox_y,rank);

		return tile_coll_map[tile_x][tile_y]->get_vox_at(vox_x,vox_y);
	}

	bool is_y_out_of_bounds(Vec3 p)
	{
		if(p.y < global_mins.y || p.y > global_maxs.y)
			return true;
		return false;
	}

	bool is_x_out_of_bounds(Vec3 p)
	{
		if(p.x < global_mins.x || p.x > global_maxs.x)
			return true;
		return false;
	}
};

#endif //PARKOUR_FLOOR_HPP
