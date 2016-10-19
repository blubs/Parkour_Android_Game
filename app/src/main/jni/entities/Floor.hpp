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
	//Subtype index of tile (used for walls)
	int tile_subtype[MAX_WIDTH][MAX_LENGTH];
	//Variant index of tile
	int tile_variant[MAX_WIDTH][MAX_LENGTH];

	//What tile set are we using?
	int interior_style;
	//What material are we using?
	int interior_variant;

	//For convenience/speed, we're going to hold an array of pointers to models and collision maps
	Collision_Map* tile_coll_map[MAX_WIDTH][MAX_LENGTH];
	Static_Model* tile_model[MAX_WIDTH][MAX_LENGTH];
	Grid_Tile* tile_object[MAX_WIDTH][MAX_LENGTH];

	Floor()
	{
		global_pos = Vec3(0,0,0);
		altitude = 0;
	}
	~Floor()
	{
	}

	void clear_floor_tiles()
	{
		for(int i = 0; i < width; i++)
		{
			for(int j = 0; j < length; j++)
			{
				tile_type[i][j] = TILE_TYPE_EMPT;
				tile_subtype[i][j] = 0;
				tile_variant[i][j] = 0;
			}
		}
	}

	//Populates the floor matrices reading generated type, subtypes, and variants
	void populate_floor()
	{
		for(int i = 0; i < width; i++)
		{
			for(int j = 0; j < length; j++)
			{
				int ttype = tile_type[i][j];
				int t_subtype = tile_subtype[i][j];

				//Setting references to models and collision maps
				Grid_Tile* obj = NULL;

				//tile_object[i][j] = Global_Tiles::instance->test_tiles[ttype];
				//TODO: do this with arrays
				switch(ttype)
				{
					default:
					case TILE_TYPE_EMPT:
						obj = Global_Tiles::instance->style[0]->empty_tile;
						break;
					case TILE_TYPE_SOLD:
						obj = Global_Tiles::instance->style[0]->solid_tile;
						break;
					case TILE_TYPE_WALL:
						//TODO: do this with arrays, too
						switch(t_subtype)
						{
							default:
							case WALL_TYPE_xXyY:
								obj = Global_Tiles::instance->style[0]->wall_xXyY;
								break;
							case WALL_TYPE_oXoY:
								obj = Global_Tiles::instance->style[0]->wall_oXoY;
								break;
							case WALL_TYPE_xooY:
								obj = Global_Tiles::instance->style[0]->wall_xooY;
								break;
							case WALL_TYPE_xoyo:
								obj = Global_Tiles::instance->style[0]->wall_xoyo;
								break;
							case WALL_TYPE_oXyo:
								obj = Global_Tiles::instance->style[0]->wall_oXyo;
								break;
							case WALL_TYPE_xXoo:
								obj = Global_Tiles::instance->style[0]->wall_xXoo;
								break;
							case WALL_TYPE_ooyY:
								obj = Global_Tiles::instance->style[0]->wall_ooyY;
								break;
							case WALL_TYPE_xoyY:
								obj = Global_Tiles::instance->style[0]->wall_xoyY;
								break;
							case WALL_TYPE_oXyY:
								obj = Global_Tiles::instance->style[0]->wall_oXyY;
								break;
							case WALL_TYPE_xXyo:
								obj = Global_Tiles::instance->style[0]->wall_xXyo;
								break;
							case WALL_TYPE_xXoY:
								obj = Global_Tiles::instance->style[0]->wall_xXoY;
								break;
						}
						break;
					case TILE_TYPE_OBST:
						switch(t_subtype)
						{
							default:
							case 0:
								obj = Global_Tiles::instance->style[0]->floor_vent;
								break;
							case 1:
								obj = Global_Tiles::instance->style[0]->wall_vent;
								break;
						}
						break;
				}
				tile_object[i][j] = obj;
				tile_coll_map[i][j] = obj->coll_map;
				tile_model[i][j] = obj->model;
			}
		}
	}

	void generate(Vec3 p, int floor_num, Vec3 mins, Vec3 maxs)
	{
		altitude = p.z + floor_num*(WINDOW_TILE_SIZE);
		global_pos = p + Vec3(0,0,floor_num*WINDOW_TILE_SIZE);
		global_mins = mins;
		global_maxs = maxs;
		global_mins.z = global_maxs.z = altitude;
		width = (int)((global_maxs.x - global_mins.x)/TILE_SIZE);
		length = (int)((global_maxs.y - global_mins.y)/TILE_SIZE);

		//FIXME: this probably shouldn't be here (sets all tile types to 0)
		clear_floor_tiles();

		//temp: explicitly setting some tiles as stuff
		tile_type[2][3] = TILE_TYPE_SOLD;
		tile_type[4][3] = TILE_TYPE_OBST;
		tile_subtype[4][3] = 0;
		tile_type[6][3] = TILE_TYPE_OBST;
		tile_subtype[6][3] = 1;

		tile_type[7][3] = TILE_TYPE_WALL;
		tile_subtype[7][3] = WALL_TYPE_xXyY;

		populate_floor();
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
		{
			LOGW("Warning: X or Y coord to check is out of bounds: coords:(%f,%f), mins:(%f,%f), maxs:(%f,%f)",p.x,p.y,global_mins.x,global_mins.y,global_maxs.x,global_maxs.y);
			return Collision_Map::VOX_SOLID;
		}

		//finding player pos relative to left near corner of floor
		p = p - global_mins;

		int tile_x = (int) floorf(p.x/TILE_SIZE);
		int tile_y = (int) floorf(p.y/TILE_SIZE);

		if(tile_x < 0 || tile_y < 0 || tile_x >= width || tile_y >= length)
		{
			LOGW("Warning: tried reaching out of bounds tile: (floor dims: (%d x %d), index: (%d x %d))",width,length,tile_x,tile_y);
			return Collision_Map::VOX_EMPTY;
		}

		Vec3 vox_p = Vec3(efmodf(p.x,TILE_SIZE),efmodf(p.y,TILE_SIZE),0);
		int vox_x = (int) (floorf(vox_p.x/GRID_SIZE));
		int vox_y = (int) (floorf(vox_p.y/GRID_SIZE));

		if(vox_x < 0 || vox_y < 0 || vox_x >= TILE_VOXEL_DIMS || vox_y >= TILE_VOXEL_DIMS)
		{
			LOGW("Warning: tried reaching out of bounds voxel: (index: (%d x %d))",vox_x,vox_y);
			return Collision_Map::VOX_EMPTY;
		}

		char rank = tile_coll_map[tile_x][tile_y]->get_vox_at(vox_x,vox_y);
		if(rank != 0)
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

	//	Returns a maneuver if there exists a maneuver in the this floor's tileset such that:
	//	(the input required to start the maneuver is input_type) AND (the player is within the bounding box required to start the maneuver)
	//	returns NULL if no such tile exists

	//==== Quick note on what tiles we have to check ====
	//Previously, the 1st keyframe of a maneuver had to lie within that tile
	//But that is no longer the case

	//As a rule of thumb, the start of the maneuver must lie within the tile itself, or the tile before it
	//so for a given player position, we must check the tile the player is on and the tile after it (+1 in y direction)
	//=====================================

	Maneuver* input_to_maneuver(Vec3 pos, int input_type)
	{
		//position given is in floor space, 0,0 being near left corner
		//get tile indices for the position
		if(is_x_out_of_bounds(pos) || is_y_out_of_bounds(pos))
		{
			LOGW("Warning: X or Y coord to check is out of bounds: coords:(%f,%f), mins:(%f,%f), maxs:(%f,%f)",pos.x,pos.y,global_mins.x,global_mins.y,global_maxs.x,global_maxs.y);
			return NULL;
		}

		//finding player pos relative to left near corner of floor
		Vec3 floor_pos = pos - global_mins;

		int tile_x = (int) floorf(floor_pos.x/TILE_SIZE);
		int tile_y = (int) floorf(floor_pos.y/TILE_SIZE);

		if(tile_x < 0 || tile_y < 0 || tile_x >= width || tile_y >= length)
		{
			LOGW("Warning: tried reaching out of bounds tile: (floor dims: (%d x %d), index: (%d x %d))",width,length,tile_x,tile_y);
			return Collision_Map::VOX_EMPTY;
		}
		//Checking the tile the player is on
		Vec3 mins;
		Vec3 maxs;
		Maneuver* man = NULL;

		//Getting player pos relative to the tile
		Vec3 p = floor_pos - Vec3(tile_x * TILE_SIZE, tile_y * TILE_SIZE, 0);
		Grid_Tile* tile = tile_object[tile_x][tile_y];

		for(int i = 0; i < tile->maneuver_count; i++)
		{
			man = tile->maneuvers[i];
			//If we have the correct input
			if(input_type & man->input_required)
			{
				//If we are in the correct area
				mins = man->keyframes[0]->mins;
				maxs = man->keyframes[0]->maxs;
				if(p.x >= mins.x && p.x <= maxs.x && p.y >= mins.y && p.y <= maxs.y)
				{
					return man;
				}
			}
		}

		//Checking the next tile
		tile_y++;

		if(tile_y >= length)
		{
			//There is no tile after
			return NULL;
		}

		//Getting player pos relative to the tile
		p = floor_pos - Vec3(tile_x * TILE_SIZE, tile_y * TILE_SIZE, 0);
		tile = tile_object[tile_x][tile_y];


		for(int i = 0; i < tile->maneuver_count; i++)
		{
			man = tile->maneuvers[i];
			//If we have the correct input
			if(input_type | man->input_required)
			{
				//If we are in the correct area
				mins = man->keyframes[0]->mins;
				maxs = man->keyframes[0]->maxs;
				if(p.x >= mins.x && p.x <= maxs.x && p.y >= mins.y && p.y <= maxs.y)
				{
					return man;
				}
			}
		}
		return NULL;
	}
	//Returns the global tile position that p lies on
	Vec3 get_tile_ofs_at_pos(Vec3 p)
	{
		p = p - global_mins;
		p = Vec3(floorf(p.x/TILE_SIZE) * TILE_SIZE,floorf(p.y/TILE_SIZE) * TILE_SIZE,0);
		p = p + global_mins;
		return p;
	}
};

#endif //PARKOUR_FLOOR_HPP
