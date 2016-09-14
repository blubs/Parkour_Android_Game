//
// Created by F1 on 9/3/2016.
//

#ifndef PARKOUR_GLOBAL_TILES_HPP
#define PARKOUR_GLOBAL_TILES_HPP

#include "../entities/Grid_Tile.hpp"

//TODO: finalize implementation of this (we are doing some starter testing things for now)
//Tile Terminology
//
//Style: the entire tile-set that makes up a style of interior
//Style Variant: different texture/material version of a tile set
//TODO: if we go with procedural colors, variants will be different textures with different features, and we will randomly choose colors to use in a shader for variety
//Type: the general navigation type of a tile
//		i.e. this tile is empty, this tile is a solid block (blocks all navigation), this tile is a wall
//			this tile has an obstacle on it, etc...
//Tile Variant: different models with potentially different traversals of a tile type

//General routine:
//
//	Building picks an exterior style and a random exterior variant
//	Building picks an interior style, and a random interior variant (if random colors, choose those)
//	Floor begins generation and populates tile types 2d array
//		This evaluates what tile types will go where
//	Floor then chooses a random variant of each tile type for each tile in the floor

//How variant materials / textures are going to be stored
//
//	Interior style holds a list of Variant_Materials
//		This class holds methods for randomizing shader color values
//		This class is responsible for the color palette generation
//		To use the material, we just call bind to bind the material
//		A method called gen_palette to make random colors

//Fallback: if palette generation fails, we can store a large array of preset interior palettes and just use those
//


#define TILE_TYPES 2//total count of tile types
#define TILE_TYPE_EMPT 0
#define TILE_TYPE_SOLD 1
//TODO: ...more tile type const identifiers

class Interior_Style
{
public:
	//TODO: how are we going to store / handle materials & textures?

	//TODO: This will hold arrays of length however many variants each type has
	Grid_Tile* tiles[TILE_TYPES];

	//Holds the number of variants per type (also the length of each array pointed to by tiles pointer array)
	int type_variant_counts[TILE_TYPES];


	Interior_Style()
	{
		tiles[0] = new Grid_Tile[2];
		type_variant_counts[0] = 2;
		tiles[1] = new Grid_Tile[3];
		type_variant_counts[1] = 3;

		//TODO: populate tile models and collision maps
		//FIXME: should probably do this in a more general way from outside this class (since different styles may have different numbers of variants)
		//tiles[1][0].coll_map = new Collision_Map();
		//tiles[1][0].model = new Static_Model("da_filename");
	}
	~Interior_Style()
	{
		for(int i = 0; i < TILE_TYPES; i++)
		{
			delete[] tiles[i];
		}
	}
};

class Global_Tiles
{
public:
	static Global_Tiles* instance;

	static void init_data()
	{
		instance = new Global_Tiles();
	}
	static void term_data()
	{
		delete instance;
	}

	Interior_Style* style[1];

	//temp remove this
	Grid_Tile* test_tiles[2];
	//end temp

	Global_Tiles()
	{
		//style[0] = new Tile_Style();

		//style[0]->type[0]->model->load_model();
		//style[0]->type[0]->collision_map = new Collision_Map();

		//For now just hold the 2 tiles explicitly
		test_tiles[TILE_TYPE_EMPT] = new Grid_Tile();
		test_tiles[TILE_TYPE_SOLD] = new Grid_Tile();

		//Setting solid tile's voxels as solid
		for(int i = 0; i < 6; i++)
		{
			for(int j = 0; j < 6; j++)
			{
				test_tiles[TILE_TYPE_SOLD]->coll_map->tile[i][j] = Collision_Map::VOX_SOLID;
			}
		}
		test_tiles[TILE_TYPE_EMPT]->model = new Static_Model("models/tiles/style0/empt0.stmf");
		test_tiles[TILE_TYPE_SOLD]->model = new Static_Model("models/tiles/style0/sold0.stmf");
	}
	~Global_Tiles()
	{
		delete test_tiles[0]->model;
		delete test_tiles[1]->model;
		delete test_tiles[0];
		delete test_tiles[1];
	}

	static void init_gl()
	{
		if(!instance)
			return;
		instance->test_tiles[0]->model->init_gl();
		instance->test_tiles[1]->model->init_gl();
	}
	static void term_gl()
	{
		if(!instance)
			return;
		instance->test_tiles[0]->model->term_gl();
		instance->test_tiles[1]->model->term_gl();
	}
};

#endif //PARKOUR_GLOBAL_TILES_HPP
