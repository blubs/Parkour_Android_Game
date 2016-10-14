//
// Created by F1 on 9/3/2016.
//

#include "Global_Tiles.hpp"


Interior_Style::Interior_Style()
{
	variants[0] = new Interior_Variant();

	tiles[0] = new Grid_Tile*[2];
	type_variant_counts[0] = 2;
	tiles[1] = new Grid_Tile*[3];
	type_variant_counts[1] = 3;

	//TODO: populate tile models and collision maps
	//FIXME: should probably do this in a more general way from outside this class (since different styles may have different numbers of variants)
	//tiles[1][0].coll_map = new Collision_Map();
	//tiles[1][0].model = new Static_Model("da_filename");
}
Interior_Style::~Interior_Style()
{
	for(int i = 0; i < TILE_TYPES; i++)
	{
		delete[] tiles[i];
	}
}

int Global_Tiles::init_data()
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

void Global_Tiles::term_data()
{
	delete instance;

	Interior_Variant::term_static_data();
}

Global_Tiles::Global_Tiles()
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
	test_tiles[TILE_TYPE_EMPT] = new Grid_Tile(0,0);
	test_tiles[TILE_TYPE_SOLD] = new Grid_Tile(0,0);

	//Two obstacle test tiles
	test_tiles[2] = new Grid_Tile(1,0);
	test_tiles[3] = new Grid_Tile(0,0);

	//Setting solid tile's voxels as solid
	for(int i = 0; i < TILE_VOXEL_DIMS; i++)
	{
		for(int j = 0; j < TILE_VOXEL_DIMS; j++)
		{
			test_tiles[TILE_TYPE_SOLD]->coll_map->voxel[i][j] = Collision_Map::VOX_SOLID;
		}
	}
	test_tiles[TILE_TYPE_EMPT]->model = new Static_Model("models/tiles/style0/empt0.stmf");
	test_tiles[TILE_TYPE_SOLD]->model = new Static_Model("models/tiles/style0/sold0.stmf");

	test_tiles[2]->model = new Static_Model("models/tiles/style0/test_vent.stmf");
	test_tiles[3]->model = new Static_Model("models/tiles/style0/test_vent2.stmf");

	//Setting test tiles collision maps
	for(int i = 0; i < TILE_VOXEL_DIMS; i++)
	{
		test_tiles[2]->coll_map->voxel[i][3] = Collision_Map::VOX_SOLID;
		test_tiles[3]->coll_map->voxel[i][3] = Collision_Map::VOX_SOLID;
	}

	//Setting up test maneuver
	test_tiles[2]->maneuvers[0] = new Maneuver(7);//7 keyframes

	//Test obstacle: has activate area from (1,0) to (2,2), then moves up way high, then moves back down, then releases at regular height.
	//4 frames.
	Keyframe** frames = test_tiles[2]->maneuvers[0]->keyframes;

	frames[0]->set_bounds(Vec3(1,0,0),Vec3(2,2,0));
	frames[0]->set_input(INPUT_SWIPE_NONE);
	frames[0]->set_speed(PLAYER_RUN_SPEED,0,0);
	frames[0]->set_lerp(FRAME_LERP_LINEAR,0);//redundant (this is default)
	frames[0]->set_orient(FRAME_ORIENT_NONE,Vec3::ZERO(),0.2);//redundant (this is default)
	frames[0]->set_anim(FRAME_ANIM_NOOP,0,ANIM_END_TYPE_ROOT_POSE);//redundant (this is default)
	frames[0]->set_vbob(CAM_VIEWBOB_NONE);//redundant (this is default)
	frames[0]->set_specflag(0);//redundant (this is default)

	//Now for the next frames, omitting redundant calls
	frames[1]->set_bounds(Vec3(1,2.1,5));
	frames[1]->set_lerp(FRAME_LERP_QUADRATIC,-9.8f);
	frames[1]->set_orient(FRAME_ORIENT_CONSTANT,Vec3(2,3,0),0.2);//face right
	frames[1]->set_speed(1,0,0);

	frames[2]->set_bounds(Vec3(1,6,5));
	frames[2]->set_lerp(FRAME_LERP_LINEAR,0);
	frames[2]->set_orient(FRAME_ORIENT_ONCE,Vec3(0,6,0),0.2);//face left
	frames[2]->set_speed(1,0,0);

	frames[3]->set_bounds(Vec3(1,9,5));
	frames[3]->set_lerp(FRAME_LERP_QUAD_TO_VERT,0);
	frames[3]->set_orient(FRAME_ORIENT_ONCE,Vec3(1,8,0),0.2);//face back
	frames[3]->set_speed(1,0,0);

	frames[4]->set_bounds(Vec3(1,14,10));
	frames[4]->set_lerp(FRAME_LERP_LINEAR,0);
	frames[4]->set_speed(1,0,0);

	frames[5]->set_bounds(Vec3(5,19,5));
	frames[5]->set_lerp(FRAME_LERP_QUAD_FROM_VERT,0);
	frames[5]->set_speed(1,0,0);

	frames[6]->set_bounds(Vec3(5,24,0));


	//TODO: continue the rest of the frames

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
Global_Tiles::~Global_Tiles()
{
	delete style[0];

	delete test_tiles[0]->model;
	delete test_tiles[1]->model;
	delete test_tiles[2]->model;
	delete test_tiles[3]->model;
	delete test_tiles[0];
	delete test_tiles[1];
	delete test_tiles[2];
	delete test_tiles[3];
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

void Global_Tiles::init_gl()
{
	if(!instance)
		return;
	instance->style[0]->variants[0]->init_gl();
	instance->test_tiles[0]->model->init_gl();
	instance->test_tiles[1]->model->init_gl();
	instance->test_tiles[2]->model->init_gl();
	instance->test_tiles[3]->model->init_gl();
	instance->window_model->init_gl();
	instance->window_shad->init_gl();
	instance->window_tex0->init_gl();

	instance->window_int_model->init_gl();
	instance->window_int_shad->init_gl();
	instance->window_int_tex0->init_gl();
	instance->window_int_misc_tex0->init_gl();
}
void Global_Tiles::term_gl()
{
	if(!instance)
		return;
	instance->style[0]->variants[0]->term_gl();
	instance->test_tiles[0]->model->term_gl();
	instance->test_tiles[1]->model->term_gl();
	instance->test_tiles[2]->model->term_gl();
	instance->test_tiles[3]->model->term_gl();
	instance->window_model->term_gl();
	instance->window_shad->term_gl();
	instance->window_tex0->term_gl();

	instance->window_int_model->term_gl();
	instance->window_int_shad->term_gl();
	instance->window_int_tex0->term_gl();
	instance->window_int_misc_tex0->term_gl();
}


Global_Tiles* Global_Tiles::instance = NULL;