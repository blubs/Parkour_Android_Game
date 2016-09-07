//
// Created by F1 on 9/3/2016.
//

#include "Global_Tiles.hpp"
#include "../engine/graphics/Static_Model.hpp"

class Collision_Map
{
public:
	//are we going to allow for arbitrarily sized tiles?

	//2 voxels per meter, 3m x 3m tile = 6v x 6v voxel map
	char tile[6][6];
	Collision_Map()
	{
	}
	~Collision_Map()
	{
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

	Tile_Style* style[1];

	Global_Tiles()
	{
		style[0] = new Tile_Style();
		//style[0]->type[0]->model->load_model();
		style[0]->type[0]->collision_map = new Collision_Map();

	}
	~Global_Tiles()
	{
	}

	static void init_gl()
	{
		if(!instance)
			return;
	}
	static void term_gl()
	{
		if(!instance)
			return;
	}
};