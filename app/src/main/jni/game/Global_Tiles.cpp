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

	//Initializing wall_subtypes to null points
	for(int i = 0; i < WALL_TYPE_COUNT; i++)
	{
		wall_subtypes[i] = NULL;
	}
	//Initializing rail_subtypes to null pointer
	for(int i = 0; i < RAIL_TYPE_COUNT; i++)
	{
		rail_subtypes[i] = NULL;
	}
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
		Shader::PARAM_M_MATRIX,
		Shader::PARAM_M_IT_MATRIX,
		Shader::PARAM_TEXTURE_DIFFUSE,
		Shader::PARAM_TEXTURE_NORMAL,
		Shader::PARAM_TEXTURE_LIGHTMAP,
		Shader::PARAM_CUBE_MAP
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
		"m",
		"m_IT",
		"tex_diff",
		"tex_nor",
		"tex_lm",
		"cube_map"
		//,"color"
	};
	//TODO: load cubemap

	Interior_Variant::init_static_data("shaders/bldg_int.vert","shaders/bldg_int.frag",shader_ptypes,shader_pnames,13);

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
	sky_cube_map = new Cube_Map("cube_maps/test_cube_map.pkm",512);

	style[0] = new Interior_Style();

	style[0]->variants[0]->diffuse_map = new Texture("textures/tiles/s0v1_diff.pkm",2048,2048);
	style[0]->variants[0]->normal_map = new Texture("textures/tiles/s0v1_nor.pkm",2048,2048);
	style[0]->variants[0]->light_map = new Texture("textures/tiles/s0_lm.pkm",2048,2048);
	style[0]->variants[0]->ref_cube_map = new Cube_Map("cube_maps/test_cube_map.pkm",512);
	//style[0]->variants[0]->misc_map = new Texture();
	//style[0] = new Tile_Style();

	//style[0]->type[0]->model->load_model();
	//style[0]->type[0]->collision_map = new Collision_Map();

	//Empty tile
	style[0]->empty_tile = new Grid_Tile(0,0);
	style[0]->empty_tile->model = new Static_Model("models/tiles/style0/empt0.stmf");
	//Solid tile
	style[0]->solid_tile = new Grid_Tile(0,0);
	for(int i = 0; i < TILE_VOXEL_DIMS; i++)
	{
		for(int j = 0; j < TILE_VOXEL_DIMS; j++)
		{
			style[0]->solid_tile->coll_map->voxel[i][j] = CLIP_SOLID;
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
		style[0]->floor_vent->coll_map->voxel[i][3] = CLIP_SOLID;
		style[0]->wall_vent->coll_map->voxel[i][3] = CLIP_SOLID;
	}

	//==================== Loading wall tiles =====================

	for(int i = 1; i < WALL_TYPE_COUNT; i++)
	{
		style[0]->wall_subtypes[i] = new Grid_Tile(0,0);
	}
	style[0]->wall_subtypes[WALL_TYPE_oXoY]->model = new Static_Model("models/tiles/style0/wall_oXoY.stmf");
	style[0]->wall_subtypes[WALL_TYPE_xooY]->model = new Static_Model("models/tiles/style0/wall_xooY.stmf");
	style[0]->wall_subtypes[WALL_TYPE_xoyo]->model = new Static_Model("models/tiles/style0/wall_xoyo.stmf");
	style[0]->wall_subtypes[WALL_TYPE_oXyo]->model = new Static_Model("models/tiles/style0/wall_oXyo.stmf");
	style[0]->wall_subtypes[WALL_TYPE_xXoo]->model = new Static_Model("models/tiles/style0/wall_xXoo.stmf");
	style[0]->wall_subtypes[WALL_TYPE_ooyY]->model = new Static_Model("models/tiles/style0/wall_ooyY.stmf");
	style[0]->wall_subtypes[WALL_TYPE_xXyY]->model = new Static_Model("models/tiles/style0/wall_xXyY.stmf");
	style[0]->wall_subtypes[WALL_TYPE_xoyY]->model = new Static_Model("models/tiles/style0/wall_xoyY.stmf");
	style[0]->wall_subtypes[WALL_TYPE_oXyY]->model = new Static_Model("models/tiles/style0/wall_oXyY.stmf");
	style[0]->wall_subtypes[WALL_TYPE_xXyo]->model = new Static_Model("models/tiles/style0/wall_xXyo.stmf");
	style[0]->wall_subtypes[WALL_TYPE_xXoY]->model = new Static_Model("models/tiles/style0/wall_xXoY.stmf");
	style[0]->wall_subtypes[WALL_TYPE_xooo]->model = new Static_Model("models/tiles/style0/wall_xooo.stmf");
	style[0]->wall_subtypes[WALL_TYPE_oXoo]->model = new Static_Model("models/tiles/style0/wall_oXoo.stmf");
	style[0]->wall_subtypes[WALL_TYPE_ooyo]->model = new Static_Model("models/tiles/style0/wall_ooyo.stmf");
	style[0]->wall_subtypes[WALL_TYPE_oooY]->model = new Static_Model("models/tiles/style0/wall_oooY.stmf");

	//Setting collision maps for wall subtype tiles
	const int center = 3;
	for(int i = 0; i <= center; i++)
	{
		for(int j = 1; j < WALL_TYPE_COUNT; j++)
		{
			//Setting the -Y axis wall as solid for all wall types that have the -Y axis wall
			if(j & WALL_TYPE_ooyo)
				style[0]->wall_subtypes[j]->coll_map->voxel[center][i] = CLIP_SOLID;

			//Setting the +Y axis wall as solid for all wall types that have the +Y axis wall
			if(j & WALL_TYPE_oooY)
				style[0]->wall_subtypes[j]->coll_map->voxel[center][center + i] = CLIP_SOLID;

			//Setting the -X axis wall as solid for all wall types that have the -X axis wall
			if(j & WALL_TYPE_xooo)
				style[0]->wall_subtypes[j]->coll_map->voxel[i][center] = CLIP_SOLID;

			//Setting the +X axis wall as solid for all wall types that have the +X axis wall
			if(j & WALL_TYPE_oXoo)
				style[0]->wall_subtypes[j]->coll_map->voxel[center + i][center] = CLIP_SOLID;
		}
	}
	//Don't have to worry about center voxel, because the above wall segments overlap


	for(int i = 1; i < RAIL_TYPE_COUNT; i++)
	{
		if(RAIL_TYPE_IS_VALID[i])
			style[0]->rail_subtypes[i] = new Grid_Tile(0,0);
	}

	//Loading rail models
	style[0]->rail_subtypes[RAIL_TYPE_L ]->model = new Static_Model("models/tiles/style0/rail_l.stmf");
	style[0]->rail_subtypes[RAIL_TYPE_R ]->model = new Static_Model("models/tiles/style0/rail_r.stmf");
	style[0]->rail_subtypes[RAIL_TYPE_TL ]->model = new Static_Model("models/tiles/style0/rail_tl.stmf");
	style[0]->rail_subtypes[RAIL_TYPE_TL2]->model = new Static_Model("models/tiles/style0/rail_tl2.stmf");
	style[0]->rail_subtypes[RAIL_TYPE_TR ]->model = new Static_Model("models/tiles/style0/rail_tr.stmf");
	style[0]->rail_subtypes[RAIL_TYPE_TR2 ]->model = new Static_Model("models/tiles/style0/rail_tr2.stmf");
	style[0]->rail_subtypes[RAIL_TYPE_LR ]->model = new Static_Model("models/tiles/style0/rail_lr.stmf");
	style[0]->rail_subtypes[RAIL_TYPE_TL_TR ]->model = new Static_Model("models/tiles/style0/rail_tl_tr.stmf");
	style[0]->rail_subtypes[RAIL_TYPE_TL2_TR2]->model = new Static_Model("models/tiles/style0/rail_tl2_tr2.stmf");
	style[0]->rail_subtypes[RAIL_TYPE_TL_TL2]->model = new Static_Model("models/tiles/style0/rail_tl_tl2.stmf");
	style[0]->rail_subtypes[RAIL_TYPE_TR_TR2]->model = new Static_Model("models/tiles/style0/rail_tr_tr2.stmf");
	style[0]->rail_subtypes[RAIL_TYPE_TL_L]->model = new Static_Model("models/tiles/style0/rail_tl_l.stmf");
	style[0]->rail_subtypes[RAIL_TYPE_TL2_R]->model = new Static_Model("models/tiles/style0/rail_tl2_r.stmf");
	style[0]->rail_subtypes[RAIL_TYPE_TR_R ]->model = new Static_Model("models/tiles/style0/rail_tr_r.stmf");
	style[0]->rail_subtypes[RAIL_TYPE_TR2_L ]->model = new Static_Model("models/tiles/style0/rail_tr2_l.stmf");

	//Setting up collision maps for rail tiles
	for(int i = 0; i < TILE_VOXEL_DIMS; i++)
	{
		//Setting the left rail as solid
		style[0]->rail_subtypes[RAIL_TYPE_L]->coll_map->voxel[6][i] = CLIP_SOLID;
		style[0]->rail_subtypes[RAIL_TYPE_LR]->coll_map->voxel[6][i] = CLIP_SOLID;
		style[0]->rail_subtypes[RAIL_TYPE_TL_L]->coll_map->voxel[6][i] = CLIP_SOLID;
		style[0]->rail_subtypes[RAIL_TYPE_TR2_L]->coll_map->voxel[6][i] = CLIP_SOLID;

		//Setting the right rail as solid
		style[0]->rail_subtypes[RAIL_TYPE_R]->coll_map->voxel[0][i] = CLIP_SOLID;
		style[0]->rail_subtypes[RAIL_TYPE_LR]->coll_map->voxel[0][i] = CLIP_SOLID;
		style[0]->rail_subtypes[RAIL_TYPE_TL2_R]->coll_map->voxel[0][i] = CLIP_SOLID;
		style[0]->rail_subtypes[RAIL_TYPE_TR_R]->coll_map->voxel[0][i] = CLIP_SOLID;

		//Setting the TR rail
		style[0]->rail_subtypes[RAIL_TYPE_TR]->coll_map->voxel[i][i] = CLIP_SOLID;
			style[0]->rail_subtypes[RAIL_TYPE_TR]->coll_map->voxel_shape[i][i] = CLIP_SHAPE_GT_POS;
		style[0]->rail_subtypes[RAIL_TYPE_TR_R]->coll_map->voxel[i][i] = CLIP_SOLID;
			style[0]->rail_subtypes[RAIL_TYPE_TR_R]->coll_map->voxel_shape[i][i] = CLIP_SHAPE_GT_POS;
		if(i > 0)
		{
			style[0]->rail_subtypes[RAIL_TYPE_TR]->coll_map->voxel[i-1][i] = CLIP_SOLID;
				style[0]->rail_subtypes[RAIL_TYPE_TR]->coll_map->voxel_shape[i-1][i] = CLIP_SHAPE_LT_POS;
		}
		if(i > 1)
		{
			style[0]->rail_subtypes[RAIL_TYPE_TR_R]->coll_map->voxel[i-1][i] = CLIP_SOLID;
			style[0]->rail_subtypes[RAIL_TYPE_TR_R]->coll_map->voxel_shape[i-1][i] = CLIP_SHAPE_LT_POS;
		}

		//Setting TR2 rail
		style[0]->rail_subtypes[RAIL_TYPE_TR2]->coll_map->voxel[i][i] = CLIP_SOLID;
		style[0]->rail_subtypes[RAIL_TYPE_TR2]->coll_map->voxel_shape[i][i] = CLIP_SHAPE_LT_POS;
		style[0]->rail_subtypes[RAIL_TYPE_TR2_L]->coll_map->voxel[i][i] = CLIP_SOLID;
		style[0]->rail_subtypes[RAIL_TYPE_TR2_L]->coll_map->voxel_shape[i][i] = CLIP_SHAPE_LT_POS;
		if(i < 6)
		{
			style[0]->rail_subtypes[RAIL_TYPE_TR2]->coll_map->voxel[i+1][i] = CLIP_SOLID;
			style[0]->rail_subtypes[RAIL_TYPE_TR2]->coll_map->voxel_shape[i+1][i] = CLIP_SHAPE_GT_POS;
		}
		if(i < 5)
		{
			style[0]->rail_subtypes[RAIL_TYPE_TR2_L]->coll_map->voxel[i+1][i] = CLIP_SOLID;
			style[0]->rail_subtypes[RAIL_TYPE_TR2_L]->coll_map->voxel_shape[i+1][i] = CLIP_SHAPE_GT_POS;
		}

		//Setting TL rail
		style[0]->rail_subtypes[RAIL_TYPE_TL]->coll_map->voxel[i][6-i] = CLIP_SOLID;
		style[0]->rail_subtypes[RAIL_TYPE_TL]->coll_map->voxel_shape[i][6-i] = CLIP_SHAPE_GT_NEG;
		style[0]->rail_subtypes[RAIL_TYPE_TL_L]->coll_map->voxel[i][6-i] = CLIP_SOLID;
		style[0]->rail_subtypes[RAIL_TYPE_TL_L]->coll_map->voxel_shape[i][6-i] = CLIP_SHAPE_GT_NEG;
		if(i < 6)
		{
			style[0]->rail_subtypes[RAIL_TYPE_TL]->coll_map->voxel[i+1][6-i] = CLIP_SOLID;
			style[0]->rail_subtypes[RAIL_TYPE_TL]->coll_map->voxel_shape[i+1][6-i] = CLIP_SHAPE_LT_NEG;
		}
		if(i < 5)
		{
			style[0]->rail_subtypes[RAIL_TYPE_TL_L]->coll_map->voxel[i+1][6-i] = CLIP_SOLID;
			style[0]->rail_subtypes[RAIL_TYPE_TL_L]->coll_map->voxel_shape[i+1][6-i] = CLIP_SHAPE_LT_NEG;
		}

		//Setting TL2 rail
		style[0]->rail_subtypes[RAIL_TYPE_TL2]->coll_map->voxel[i][6-i] = CLIP_SOLID;
		style[0]->rail_subtypes[RAIL_TYPE_TL2]->coll_map->voxel_shape[i][6-i] = CLIP_SHAPE_LT_NEG;
		style[0]->rail_subtypes[RAIL_TYPE_TL2_R]->coll_map->voxel[i][6-i] = CLIP_SOLID;
		style[0]->rail_subtypes[RAIL_TYPE_TL2_R]->coll_map->voxel_shape[i][6-i] = CLIP_SHAPE_LT_NEG;
		if(i > 0)
		{
			style[0]->rail_subtypes[RAIL_TYPE_TL2]->coll_map->voxel[i-1][6-i] = CLIP_SOLID;
			style[0]->rail_subtypes[RAIL_TYPE_TL2]->coll_map->voxel_shape[i-1][6-i] = CLIP_SHAPE_GT_NEG;
		}
		if(i > 1)
		{
			style[0]->rail_subtypes[RAIL_TYPE_TL2_R]->coll_map->voxel[i-1][6-i] = CLIP_SOLID;
			style[0]->rail_subtypes[RAIL_TYPE_TL2_R]->coll_map->voxel_shape[i-1][6-i] = CLIP_SHAPE_GT_NEG;
		}

		//Setting TR & TR2 tile
		style[0]->rail_subtypes[RAIL_TYPE_TR_TR2]->coll_map->voxel[i][i] = CLIP_SOLID;
		style[0]->rail_subtypes[RAIL_TYPE_TR_TR2]->coll_map->voxel_shape[i][i] = CLIP_SHAPE_IN_WALL_POS;
		//Setting TL & TL2 tile
		style[0]->rail_subtypes[RAIL_TYPE_TL_TL2]->coll_map->voxel[i][6-i] = CLIP_SOLID;
		style[0]->rail_subtypes[RAIL_TYPE_TL_TL2]->coll_map->voxel_shape[i][6-i] = CLIP_SHAPE_IN_WALL_NEG;



		//Setting the TR & TL tile
		if(i < 3)
		{
			style[0]->rail_subtypes[RAIL_TYPE_TL_TR]->coll_map->voxel[i][6-i] = CLIP_SOLID;
			style[0]->rail_subtypes[RAIL_TYPE_TL_TR]->coll_map->voxel_shape[i][6-i] = CLIP_SHAPE_GT_NEG;
		}
		else if(i == 3)
		{
			style[0]->rail_subtypes[RAIL_TYPE_TL_TR]->coll_map->voxel[i][i] = CLIP_SOLID;
			style[0]->rail_subtypes[RAIL_TYPE_TL_TR]->coll_map->voxel_shape[i][i] = CLIP_SHAPE_GT_ABS;
		}
		else
		{
			style[0]->rail_subtypes[RAIL_TYPE_TL_TR]->coll_map->voxel[i][i] = CLIP_SOLID;
			style[0]->rail_subtypes[RAIL_TYPE_TL_TR]->coll_map->voxel_shape[i][i] = CLIP_SHAPE_GT_POS;
		}
		//Setting the TR2 and TL2 tile
		if(i < 3)
		{
			style[0]->rail_subtypes[RAIL_TYPE_TL2_TR2]->coll_map->voxel[i][i] = CLIP_SOLID;
			style[0]->rail_subtypes[RAIL_TYPE_TL2_TR2]->coll_map->voxel_shape[i][i] = CLIP_SHAPE_LT_POS;
		}
		else if(i == 3)
		{
			style[0]->rail_subtypes[RAIL_TYPE_TL2_TR2]->coll_map->voxel[i][i] = CLIP_SOLID;
			style[0]->rail_subtypes[RAIL_TYPE_TL2_TR2]->coll_map->voxel_shape[i][i] = CLIP_SHAPE_LT_ABS;
		}
		else
		{
			style[0]->rail_subtypes[RAIL_TYPE_TL2_TR2]->coll_map->voxel[i][6-i] = CLIP_SOLID;
			style[0]->rail_subtypes[RAIL_TYPE_TL2_TR2]->coll_map->voxel_shape[i][6-i] = CLIP_SHAPE_LT_NEG;
		}
	}


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
	//window_model = new Static_Model("models/windows/style0.stmf");
	//window_int_model = new Static_Model("models/windows/style0_int.stmf");

	window_models = new Window_Model_Holder("models/windows/style0.stmf");

	int_window_models = new Interior_Window_Model_Holder("models/windows/style0_int.stmf");

	//Initializing window exterior shader

	GLuint shader_ptypes[] =
	{
		Shader::PARAM_VERTICES,
		Shader::PARAM_VERT_UV1,
		Shader::PARAM_VERT_NORMALS,
		Shader::PARAM_VERT_BINORMALS,
		Shader::PARAM_VERT_TANGENTS,
		Shader::PARAM_MVP_MATRIX,
		Shader::PARAM_M_MATRIX,
		Shader::PARAM_M_IT_MATRIX,
		Shader::PARAM_TEXTURE_DIFFUSE,
		Shader::PARAM_TEXTURE_NORMAL,
		Shader::PARAM_CUBE_MAP
	};
	const char *shader_pnames[] =
	{
		"vert_pos",
		"vert_uv_1",
		"vert_nor",
		"vert_binor",
		"vert_tan",
		"mvp",
		"m",
		"m_IT",
		"tex_diff",
		"tex_nor",
		"cube_map"
	};
	window_shad = new Shader("shaders/bldg_ext.vert","shaders/bldg_ext.frag",shader_ptypes,shader_pnames,11);

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
		Shader::PARAM_M_MATRIX,
		Shader::PARAM_M_IT_MATRIX,
		Shader::PARAM_TEXTURE_DIFFUSE,
		Shader::PARAM_TEXTURE_NORMAL,
		Shader::PARAM_TEXTURE_MISC,
		Shader::PARAM_CUBE_MAP
	};
	const char *pnames2[] =
	{
		"vert_pos",
		"vert_uv_1",
		"vert_nor",
		"vert_binor",
		"vert_tan",
		"mvp",
		"m",
		"m_IT",
		"tex_diff",
		"tex_nor",
		"tex_misc",
		"cube_map"
	};
	LOGE("Global Tiles 5");
	/*"vert_pos",
		"vert_uv_1",
		"vert_uv_2",==== excluded
		"vert_nor",
		"vert_binor",
		"vert_tan",
		"mvp",
		"m",
		"m_IT",
		"tex_diff",
		"tex_nor",
		"tex_lm",
		"cube_map"*/
	window_int_shad = new Shader("shaders/bldgwin_int.vert","shaders/bldgwin_int.frag",ptypes2,pnames2,12);

	window_int_mat = new Material();
	window_int_mat->set_shader(window_int_shad);
	window_int_tex0 = new Texture("textures/windows/variant0.pkm",512,512);
	window_int_misc_tex0 = new Texture("textures/windows/variant0_int_misc.pkm",512,512);
}
Global_Tiles::~Global_Tiles()
{
	delete sky_cube_map;
	delete style[0];

	//============== Deleting Interior Style ============

	delete style[0]->solid_tile->model;
	delete style[0]->solid_tile;
	delete style[0]->empty_tile->model;
	delete style[0]->empty_tile;

	for(int i = 1; i < WALL_TYPE_COUNT; i++)
	{
		delete style[0]->wall_subtypes[i]->model;
		delete style[0]->wall_subtypes[i];
	}

	for(int i = 1; i < RAIL_TYPE_COUNT; i++)
	{
		if(style[0]->rail_subtypes[i])
		{
			delete style[0]->rail_subtypes[i]->model;
			delete style[0]->rail_subtypes[i];
		}
	}

	delete style[0]->floor_vent->model;
	delete style[0]->floor_vent;
	delete style[0]->wall_vent->model;
	delete style[0]->wall_vent;

	//===================================================
	delete window_models;
	delete int_window_models;
	//delete window_model;
	delete window_mat;
	delete window_shad;
	delete window_tex0;

	//delete window_int_model;
	delete window_int_mat;
	delete window_int_shad;
	delete window_int_tex0;
	delete window_int_misc_tex0;
}

void Global_Tiles::init_gl()
{
	if(!instance)
		return;
	instance->sky_cube_map->init_gl();
	instance->style[0]->variants[0]->init_gl();

	//==================== Style 0 models init gl ===================
	instance->style[0]->solid_tile->model->init_gl();
	instance->style[0]->empty_tile->model->init_gl();

	for(int i = 1; i < WALL_TYPE_COUNT; i++)
	{
		instance->style[0]->wall_subtypes[i]->model->init_gl();
	}

	for(int i = 1; i < RAIL_TYPE_COUNT; i++)
	{
		if(RAIL_TYPE_IS_VALID[i])
		{
			instance->style[0]->rail_subtypes[i]->model->init_gl();
		}
	}

	instance->style[0]->floor_vent->model->init_gl();
	instance->style[0]->wall_vent->model->init_gl();
	//===============================================================

	instance->window_models->init_gl();
	instance->int_window_models->init_gl();

	//instance->window_model->init_gl();
	instance->window_shad->init_gl();
	instance->window_tex0->init_gl();

	//instance->window_int_model->init_gl();
	instance->window_int_shad->init_gl();
	instance->window_int_tex0->init_gl();
	instance->window_int_misc_tex0->init_gl();
}
void Global_Tiles::term_gl()
{
	if(!instance)
		return;
	instance->sky_cube_map->term_gl();
	instance->style[0]->variants[0]->term_gl();

	//==================== Style 0 models term gl ===================
	instance->style[0]->solid_tile->model->term_gl();
	instance->style[0]->empty_tile->model->term_gl();

	for(int i = 1; i < WALL_TYPE_COUNT; i++)
	{
		instance->style[0]->wall_subtypes[i]->model->term_gl();
	}

	for(int i = 1; i < RAIL_TYPE_COUNT; i++)
	{
		if(RAIL_TYPE_IS_VALID[i])
		{
			instance->style[0]->rail_subtypes[i]->model->term_gl();
		}
	}

	instance->style[0]->floor_vent->model->term_gl();
	instance->style[0]->wall_vent->model->term_gl();
	//===============================================================

	instance->window_models->term_gl();
	instance->int_window_models->term_gl();
	instance->int_window_models->term_gl();
	//instance->window_model->term_gl();
	instance->window_shad->term_gl();
	instance->window_tex0->term_gl();

	//instance->window_int_model->term_gl();
	instance->window_int_shad->term_gl();
	instance->window_int_tex0->term_gl();
	instance->window_int_misc_tex0->term_gl();
}


Global_Tiles* Global_Tiles::instance = NULL;