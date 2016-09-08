//
// Created by F1 on 9/3/2016.
//

#ifndef PARKOUR_GLOBAL_TILES_HPP
#define PARKOUR_GLOBAL_TILES_HPP

//
// Created by F1 on 9/3/2016.
//

#include "../engine/graphics/Static_Model.hpp"

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

//Since variants are just alternate textures, there is no need to have different models/collision maps per variant
/*class Tile_Variant
{
public:
	Static_Model* model;
	Collision_Map* collision_map;
};*/

class Tile_Type
{
public:
	//TODO: tile type const identifiers
	//Tile_Variant* variant[1];

	Static_Model* model;
	Collision_Map* coll_map;

	Tile_Type()
	{
		//model = new Static_Model("filename");
		//have to instantiate at load
		coll_map = new Collision_Map();
	}

	~Tile_Type()
	{
		//delete model on unload
		delete coll_map;
	}
};

class Tile_Style
{
public:
	Tile_Type* type[2];

	Tile_Style()
	{
		type[0] = new Tile_Type();
		type[1] = new Tile_Type();
	}
	~Tile_Style()
	{
	}
};

class Global_Tiles
{
public:
	static Global_Tiles* instance = NULL;

	static void init_data()
	{
		instance = new Global_Tiles();
	}
	static void term_data()
	{
		delete instance;
	}

	Tile_Style* style[1];

	//temp remove this
	Tile_Type* empt_tile;
	Tile_Type* sold_tile;
	//end temp

	Global_Tiles()
	{
		//style[0] = new Tile_Style();

		//style[0]->type[0]->model->load_model();
		//style[0]->type[0]->collision_map = new Collision_Map();

		//For now just hold the 2 tiles explicitly
		empt_tile = new Tile_Type();
		sold_tile = new Tile_Type();

		//Setting sold tile's voxels as solid
		for(int i = 0; i < 6; i++)
		{
			for(int j = 0; j < 6; j++)
			{
				sold_tile->coll_map->tile[i][j] = Collision_Map::VOX_EMPTY;
			}
		}

		empt_tile->model = new Static_Model("models/tiles/style0/empt0.stmf");
		sold_tile->model = new Static_Model("models/tiles/style0/sold0.stmf");
	}
	~Global_Tiles()
	{
		delete empt_tile->model;
		delete sold_tile->model;
		delete empt_tile;
		delete sold_tile;
	}

	static void init_gl()
	{
		if(!instance)
			return;
		instance->empt_tile->model->init_gl();
		instance->sold_tile->model->init_gl();
	}
	static void term_gl()
	{
		if(!instance)
			return;
		instance->empt_tile->model->term_gl();
		instance->sold_tile->model->term_gl();
	}
};

#endif //PARKOUR_GLOBAL_TILES_HPP
