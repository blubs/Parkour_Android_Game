//
// Created by F1 on 9/3/2016.
//

#ifndef PARKOUR_GLOBAL_TILES_HPP
#define PARKOUR_GLOBAL_TILES_HPP

#include "../entities/Grid_Tile.hpp"
#include "Interior_Variant.hpp"

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

	Interior_Variant* variants[1];

	Grid_Tile* tiles[TILE_TYPES];

	//Holds the number of variants per type (also the length of each array pointed to by tiles pointer array)
	int type_variant_counts[TILE_TYPES];


	Interior_Style()
	{
		variants[0] = new Interior_Variant();

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

	static int init_data()
	{
		GLuint shader_ptypes[] =
		{
			Shader::PARAM_VERTICES,
			Shader::PARAM_VERT_UV1,
			Shader::PARAM_VERT_UV2,
			Shader::PARAM_VERT_NORMALS,
			Shader::PARAM_VERT_BINORMALS,
			Shader::PARAM_VERT_TANGENTS,
			Shader::PARAM_MVP_MATRIX,
			Shader::PARAM_M_IT_MATRIX,
			Shader::PARAM_TEXTURE_DIFFUSE,
			Shader::PARAM_TEXTURE_NORMAL,
			Shader::PARAM_TEXTURE_LIGHTMAP
			//,Shader::PARAM_COLOR_MULT
		};
		const char *shader_pnames[] =
		{
			"vert_pos",
			"vert_uv_1",
			"vert_uv_2",
			"vert_nor",
			"vert_binor",
			"vert_tan",
			"mvp",
			"m_IT",
			"tex_diff",
			"tex_nor",
			"tex_lm"
			//,"color"
		};

		Interior_Variant::init_static_data("shaders/bldg_int.vert","shaders/bldg_int.frag",shader_ptypes,shader_pnames,11);

		instance = new Global_Tiles();

		return 1;
	}
	static void term_data()
	{
		delete instance;

		Interior_Variant::term_static_data();
	}

	Interior_Style* style[1];

	//temp remove this
	Grid_Tile* test_tiles[2];

	Static_Model* window_int_model;
	Material* window_int_mat;
	Shader* window_int_shad;
	Texture* window_int_tex0;
	Texture* window_int_misc_tex0;

	Static_Model* window_model;
	Material* window_mat;
	Shader* window_shad;
	Texture* window_tex0;
	//end temp

	Global_Tiles()
	{
		style[0] = new Interior_Style();

		style[0]->variants[0]->diffuse_map = new Texture("textures/tiles/s0v1_diff.pkm",2048,2048);
		style[0]->variants[0]->normal_map = new Texture("textures/tiles/s0v1_diff.pkm",2048,2048);
		style[0]->variants[0]->light_map = new Texture("textures/tiles/s0_lm.pkm",2048,2048);
		//style[0]->variants[0]->misc_map = new Texture();

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
		window_model = new Static_Model("models/windows/style0.stmf");
		window_int_model = new Static_Model("models/windows/style0_int.stmf");

		//Initializing window exterior shader

		GLuint shader_ptypes[] =
		{
			Shader::PARAM_VERTICES,
			Shader::PARAM_VERT_UV1,
			Shader::PARAM_VERT_NORMALS,
			Shader::PARAM_VERT_BINORMALS,
			Shader::PARAM_VERT_TANGENTS,
			Shader::PARAM_MVP_MATRIX,
			Shader::PARAM_M_IT_MATRIX,
			Shader::PARAM_TEXTURE_DIFFUSE,
			Shader::PARAM_TEXTURE_NORMAL
		};
		const char *shader_pnames[] =
		{
			"vert_pos",
			"vert_uv_1",
			"vert_nor",
			"vert_binor",
			"vert_tan",
			"mvp",
			"m_IT",
			"tex_diff",
			"tex_nor"
		};
		window_shad = new Shader("shaders/bldg_ext.vert","shaders/bldg_ext.frag",shader_ptypes,shader_pnames,9);

		window_mat = new Material();
		window_mat->set_shader(window_shad);
		window_tex0 = new Texture("textures/windows/variant0.pkm",512,512);


		GLuint ptypes2[] =
		{
			Shader::PARAM_VERTICES,
			Shader::PARAM_VERT_UV1,
			Shader::PARAM_VERT_NORMALS,
			Shader::PARAM_VERT_BINORMALS,
			Shader::PARAM_VERT_TANGENTS,
			Shader::PARAM_MVP_MATRIX,
			Shader::PARAM_M_IT_MATRIX,
			Shader::PARAM_TEXTURE_DIFFUSE,
			Shader::PARAM_TEXTURE_NORMAL,
			Shader::PARAM_TEXTURE_MISC
		};
		const char *pnames2[] =
		{
			"vert_pos",
			"vert_uv_1",
			"vert_nor",
			"vert_binor",
			"vert_tan",
			"mvp",
			"m_IT",
			"tex_diff",
			"tex_nor",
			"tex_misc"
		};
		window_int_shad = new Shader("shaders/bldgwin_int.vert","shaders/bldgwin_int.frag",ptypes2,pnames2,10);

		window_int_mat = new Material();
		window_int_mat->set_shader(window_int_shad);
		window_int_tex0 = new Texture("textures/windows/variant0.pkm",512,512);
		window_int_misc_tex0 = new Texture("textures/windows/variant0_int_misc.pkm",512,512);

	}
	~Global_Tiles()
	{
		delete style[0];

		delete test_tiles[0]->model;
		delete test_tiles[1]->model;
		delete test_tiles[0];
		delete test_tiles[1];
		delete window_model;
		delete window_mat;
		delete window_shad;
		delete window_tex0;

		delete window_int_model;
		delete window_int_mat;
		delete window_int_shad;
		delete window_int_tex0;
		delete window_int_misc_tex0;
	}

	static void init_gl()
	{
		if(!instance)
			return;
		instance->style[0]->variants[0]->init_gl();
		instance->test_tiles[0]->model->init_gl();
		instance->test_tiles[1]->model->init_gl();
		instance->window_model->init_gl();
		instance->window_shad->init_gl();
		instance->window_tex0->init_gl();

		instance->window_int_model->init_gl();
		instance->window_int_shad->init_gl();
		instance->window_int_tex0->init_gl();
		instance->window_int_misc_tex0->init_gl();
	}
	static void term_gl()
	{
		if(!instance)
			return;
		instance->style[0]->variants[0]->term_gl();
		instance->test_tiles[0]->model->term_gl();
		instance->test_tiles[1]->model->term_gl();
		instance->window_model->term_gl();
		instance->window_shad->term_gl();
		instance->window_tex0->term_gl();

		instance->window_int_model->term_gl();
		instance->window_int_shad->term_gl();
		instance->window_int_tex0->term_gl();
		instance->window_int_misc_tex0->term_gl();
	}
};

#endif //PARKOUR_GLOBAL_TILES_HPP
