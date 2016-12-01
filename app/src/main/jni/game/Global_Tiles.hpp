//
// Created by F1 on 9/3/2016.
//

#ifndef PARKOUR_GLOBAL_TILES_HPP
#define PARKOUR_GLOBAL_TILES_HPP

#include "../entities/Grid_Tile.hpp"
#include "Interior_Variant.hpp"
#include "Window_Model_Holder.hpp"

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


class Interior_Style
{
public:
	//TODO: how are we going to store / handle materials & textures?

	//TODO: This will hold arrays of length however many variants each type has

	//Holds materials,diffuse, normal, and lightmap textures for this Interior Style
	Interior_Variant* variants[1];

	//TODO: use tiles
	Grid_Tile** tiles[TILE_TYPES];

	//For now, holding explicit references to the tiles
	Grid_Tile* solid_tile;
	Grid_Tile* empty_tile;
	//Wall tiles:

	Grid_Tile* wall_subtypes[WALL_TYPE_COUNT] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};

	Grid_Tile* tun_right;
	Grid_Tile* tun_left;
	Grid_Tile* tun_r2l;
	Grid_Tile* tun_l2r;

	/*//Corners
	Grid_Tile* wall_oXoY;
	Grid_Tile* wall_xooY;
	Grid_Tile* wall_xoyo;
	Grid_Tile* wall_oXyo;
	//Straight walls
	Grid_Tile* wall_xXoo;
	Grid_Tile* wall_ooyY;
	//Cross
	Grid_Tile* wall_xXyY;
	//T-walls
	Grid_Tile* wall_xoyY;
	Grid_Tile* wall_oXyY;
	Grid_Tile* wall_xXyo;
	Grid_Tile* wall_xXoY;
	//Wall segments
	Grid_Tile* wall_xooo;
	Grid_Tile* wall_oXoo;
	Grid_Tile* wall_ooyo;
	Grid_Tile* wall_oooY;*/


	//Test collision tiles
	Grid_Tile* floor_vent;
	Grid_Tile* wall_vent;

	//Holds the number of variants per type (also the length of each array pointed to by tiles pointer array)
	int type_variant_counts[TILE_TYPES];


	Interior_Style();
	~Interior_Style();
};

class Global_Tiles
{
public:
	static Global_Tiles* instance;

	static int init_data();
	static void term_data();

	Interior_Style* style[1];

	//Used for both skybox and building exterior reflections
	Cube_Map* sky_cube_map = NULL;

	//temp remove this
	//Static_Model* window_int_model;
	Material* window_int_mat;
	Shader* window_int_shad;
	Texture* window_int_tex0;
	Texture* window_int_misc_tex0;

	Window_Model_Holder* window_models;
	Interior_Window_Model_Holder* int_window_models;
	//Static_Model* window_model;
	Material* window_mat;
	Shader* window_shad;
	Texture* window_tex0;
	//end temp

	Global_Tiles();
	~Global_Tiles();
	static void init_gl();
	static void term_gl();
};

#endif //PARKOUR_GLOBAL_TILES_HPP
