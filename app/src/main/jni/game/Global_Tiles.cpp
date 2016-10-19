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
	//Empty tile
	style[0]->empty_tile = new Grid_Tile(0,0);
	style[0]->empty_tile->model = new Static_Model("models/tiles/style0/empt0.stmf");
	//Solid tile
	style[0]->solid_tile = new Grid_Tile(0,0);
	for(int i = 0; i < TILE_VOXEL_DIMS; i++)
	{
		for(int j = 0; j < TILE_VOXEL_DIMS; j++)
		{
			style[0]->solid_tile->coll_map->voxel[i][j] = Collision_Map::VOX_SOLID;
		}
	}
	style[0]->solid_tile->model = new Static_Model("models/tiles/style0/sold0.stmf");
	//Test obstacle tiles
	style[0]->floor_vent = new Grid_Tile(1,0);
	style[0]->floor_vent->model = new Static_Model("models/tiles/style0/test_vent.stmf");


	style[0]->wall_vent = new Grid_Tile(0,0);
	style[0]->wall_vent->model = new Static_Model("models/tiles/style0/test_vent2.stmf");

	for(int i = 0; i < TILE_VOXEL_DIMS; i++)
	{
		style[0]->floor_vent->coll_map->voxel[i][3] = Collision_Map::VOX_SOLID;
		style[0]->wall_vent->coll_map->voxel[i][3] = Collision_Map::VOX_SOLID;
	}

	//==================== Loading wall tiles =====================

	style[0]->wall_oXoY = new Grid_Tile(0,0);
	style[0]->wall_xooY = new Grid_Tile(0,0);
	style[0]->wall_xoyo = new Grid_Tile(0,0);
	style[0]->wall_oXyo = new Grid_Tile(0,0);
	style[0]->wall_xXoo = new Grid_Tile(0,0);
	style[0]->wall_ooyY = new Grid_Tile(0,0);
	style[0]->wall_xXyY = new Grid_Tile(0,0);
	style[0]->wall_xoyY = new Grid_Tile(0,0);
	style[0]->wall_oXyY = new Grid_Tile(0,0);
	style[0]->wall_xXyo = new Grid_Tile(0,0);
	style[0]->wall_xXoY = new Grid_Tile(0,0);

	style[0]->wall_oXoY->model = new Static_Model("models/tiles/style0/wall_oXoY.stmf");
	style[0]->wall_xooY->model = new Static_Model("models/tiles/style0/wall_xooY.stmf");
	style[0]->wall_xoyo->model = new Static_Model("models/tiles/style0/wall_xoyo.stmf");
	style[0]->wall_oXyo->model = new Static_Model("models/tiles/style0/wall_oXyo.stmf");
	style[0]->wall_xXoo->model = new Static_Model("models/tiles/style0/wall_xXoo.stmf");
	style[0]->wall_ooyY->model = new Static_Model("models/tiles/style0/wall_ooyY.stmf");
	style[0]->wall_xXyY->model = new Static_Model("models/tiles/style0/wall_xXyY.stmf");
	style[0]->wall_xoyY->model = new Static_Model("models/tiles/style0/wall_xoyY.stmf");
	style[0]->wall_oXyY->model = new Static_Model("models/tiles/style0/wall_oXyY.stmf");
	style[0]->wall_xXyo->model = new Static_Model("models/tiles/style0/wall_xXyo.stmf");
	style[0]->wall_xXoY->model = new Static_Model("models/tiles/style0/wall_xXoY.stmf");

	//=============================================================

	//========= Setting up Maneuvers ===============

	//Setting up test maneuver
	style[0]->floor_vent->maneuvers[0] = new Maneuver(6);//6 keyframes
	style[0]->floor_vent->maneuvers[0]->set_input(INPUT_SWIPE_UP);

	//Test obstacle: has activate area from (1,0) to (2,2), then moves up way high, then moves back down, then releases at regular height.
	//4 frames.
	Keyframe** frames = style[0]->floor_vent->maneuvers[0]->keyframes;

	frames[0]->set_bounds(Vec3(1,0,0),Vec3(2.5,2,0));
	frames[0]->set_speed(0.5f,0,0);
	frames[0]->set_lerp(FRAME_LERP_LINEAR,0);//redundant (this is default)
	frames[0]->set_orient(FRAME_ORIENT_NONE,Vec3::ZERO(),0.1);//redundant (this is default)
	frames[0]->set_anim(FRAME_ANIM_NOOP,0,ANIM_END_TYPE_ROOT_POSE);//redundant (this is default)
	frames[0]->set_vbob(CAM_VIEWBOB_RUNNING);//redundant (this is default)
	frames[0]->set_specflag(0);//redundant (this is default)

	//Now for the next frames, omitting redundant calls
	frames[1]->set_bounds(Vec3(1.75f,4,0));
	frames[1]->set_speed(0.5f,0,0);
	frames[1]->set_anim(FRAME_ANIM_PAUSE);

	frames[2]->set_bounds(Vec3(1.75f,6,0));
	frames[2]->set_speed(0.5f,0,0);
	frames[2]->set_anim(FRAME_ANIM_RESUME);

	frames[3]->set_bounds(Vec3(1.75f,8,0));
	frames[3]->set_speed(0.5f,0,0);
	frames[3]->set_anim(FRAME_ANIM_STOP);

	frames[4]->set_bounds(Vec3(1.75f,10,0));
	frames[4]->set_speed(0.5f,0,0);
	frames[4]->set_anim(FRAME_ANIM_PLAY,PLAYER_ANIM_SPEED_VAULT,ANIM_END_TYPE_FREEZE);

	frames[5]->set_bounds(Vec3(1.75f,12,0));


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

	//============== Deleting Interior Style ============

	delete style[0]->solid_tile->model;
	delete style[0]->solid_tile;
	delete style[0]->empty_tile->model;
	delete style[0]->empty_tile;
	delete style[0]->wall_oXoY->model;
	delete style[0]->wall_oXoY;
	delete style[0]->wall_xooY->model;
	delete style[0]->wall_xooY;
	delete style[0]->wall_xoyo->model;
	delete style[0]->wall_xoyo;
	delete style[0]->wall_oXyo->model;
	delete style[0]->wall_oXyo;
	delete style[0]->wall_xXoo->model;
	delete style[0]->wall_xXoo;
	delete style[0]->wall_ooyY->model;
	delete style[0]->wall_ooyY;
	delete style[0]->wall_xXyY->model;
	delete style[0]->wall_xXyY;
	delete style[0]->wall_xoyY->model;
	delete style[0]->wall_xoyY;
	delete style[0]->wall_oXyY->model;
	delete style[0]->wall_oXyY;
	delete style[0]->wall_xXyo->model;
	delete style[0]->wall_xXyo;
	delete style[0]->wall_xXoY->model;
	delete style[0]->wall_xXoY;
	delete style[0]->floor_vent->model;
	delete style[0]->floor_vent;
	delete style[0]->wall_vent->model;
	delete style[0]->wall_vent;

	//===================================================


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

	//==================== Style 0 models init gl ===================
	instance->style[0]->solid_tile->model->init_gl();
	instance->style[0]->empty_tile->model->init_gl();
	instance->style[0]->wall_oXoY->model->init_gl();
	instance->style[0]->wall_xooY->model->init_gl();
	instance->style[0]->wall_xoyo->model->init_gl();
	instance->style[0]->wall_oXyo->model->init_gl();
	instance->style[0]->wall_xXoo->model->init_gl();
	instance->style[0]->wall_ooyY->model->init_gl();
	instance->style[0]->wall_xXyY->model->init_gl();
	instance->style[0]->wall_xoyY->model->init_gl();
	instance->style[0]->wall_oXyY->model->init_gl();
	instance->style[0]->wall_xXyo->model->init_gl();
	instance->style[0]->wall_xXoY->model->init_gl();
	instance->style[0]->floor_vent->model->init_gl();
	instance->style[0]->wall_vent->model->init_gl();
	//===============================================================

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

	//==================== Style 0 models term gl ===================
	instance->style[0]->solid_tile->model->term_gl();
	instance->style[0]->empty_tile->model->term_gl();
	instance->style[0]->wall_oXoY->model->term_gl();
	instance->style[0]->wall_xooY->model->term_gl();
	instance->style[0]->wall_xoyo->model->term_gl();
	instance->style[0]->wall_oXyo->model->term_gl();
	instance->style[0]->wall_xXoo->model->term_gl();
	instance->style[0]->wall_ooyY->model->term_gl();
	instance->style[0]->wall_xXyY->model->term_gl();
	instance->style[0]->wall_xoyY->model->term_gl();
	instance->style[0]->wall_oXyY->model->term_gl();
	instance->style[0]->wall_xXyo->model->term_gl();
	instance->style[0]->wall_xXoY->model->term_gl();
	instance->style[0]->floor_vent->model->term_gl();
	instance->style[0]->wall_vent->model->term_gl();
	//===============================================================

	instance->window_model->term_gl();
	instance->window_shad->term_gl();
	instance->window_tex0->term_gl();

	instance->window_int_model->term_gl();
	instance->window_int_shad->term_gl();
	instance->window_int_tex0->term_gl();
	instance->window_int_misc_tex0->term_gl();
}


Global_Tiles* Global_Tiles::instance = NULL;