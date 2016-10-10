//
// Created by F1 on 8/2/2016.
//

#include "Game.hpp"

int Game::load_shaders ()
{
	//Initializing shaders

	//Test shader
	GLuint pt1[] =
	{
		Shader::PARAM_VERTICES,
		Shader::PARAM_VERT_COLORS,
		Shader::PARAM_VERT_UV1,
		Shader::PARAM_TEXTURE_DIFFUSE,
		Shader::PARAM_MVP_MATRIX,
		Shader::PARAM_TEST_FIELD
	};
	const char *pn1[] =
	{
		"vert_pos",
		"fill_color",
		"src_tex_coord",
		"tex",
		"mvp",
		"test_color_param"
	};
	test_shader = new Shader("shaders/minimal.vert","shaders/minimal.frag",pt1,pn1,6);

	//Text shader
	GLuint pt2[] =
	{
		Shader::PARAM_VERTICES,
		Shader::PARAM_VERT_UV1,
		Shader::PARAM_TEXTURE_DIFFUSE,
		Shader::PARAM_MVP_MATRIX,
		Shader::PARAM_COLOR_MULT,
		Shader::PARAM_COLOR_ADD
	};
	const char *pn2[] =
	{
		"vert_pos",
		"src_tex_coord",
		"tex",
		"mvp",
		"mult_color",
		"add_color"
	};
	text_shader = new Shader("shaders/monochrome_transparent.vert","shaders/monochrome_transparent.frag",pt2,pn2,6);

	//Skeleton test shader
	GLuint pt3[] =
	{
		Shader::PARAM_VERTICES,
		Shader::PARAM_VERT_UV1,
		Shader::PARAM_VERT_NORMALS,
		Shader::PARAM_MVP_MATRIX,
		Shader::PARAM_M_IT_MATRIX,
		Shader::PARAM_BONE_INDICES,
		Shader::PARAM_BONE_WEIGHTS,
		Shader::PARAM_BONE_MATRICES,
		Shader::PARAM_BONE_IT_MATRICES
	};
	const char *pn3[] =
	{
		"vert_pos",
		"vert_uv",
		"vert_nor",
		"mvp",
		"m_IT",
		"bone_index",
		"bone_weight",
		"bone",
		"bone_IT"
	};
	skel_color_shader = new Shader("shaders/skeletal_color.vert","shaders/skeletal_color.frag",pt3,pn3,9);

	//Player skin shader
	GLuint pt4[] =
	{
		Shader::PARAM_VERTICES,
		Shader::PARAM_VERT_UV1,
		Shader::PARAM_VERT_NORMALS,
		Shader::PARAM_VERT_TANGENTS,
		Shader::PARAM_VERT_BINORMALS,
		Shader::PARAM_TEXTURE_NORMAL,
		Shader::PARAM_TEXTURE_DIFFUSE,
		Shader::PARAM_MVP_MATRIX,
		Shader::PARAM_M_IT_MATRIX,
		Shader::PARAM_BONE_INDICES,
		Shader::PARAM_BONE_WEIGHTS,
		Shader::PARAM_BONE_MATRICES,
		Shader::PARAM_BONE_IT_MATRICES
	};
	const char *pn4[] =
	{
		"vert_pos",
		"vert_uv",
		"vert_nor",
		"vert_tan",
		"vert_binor",
		"tex_nor",
		"tex_diff",
		"mvp",
		"m_IT",
		"bone_index",
		"bone_weight",
		"bone",
		"bone_IT"
	};
	player_skin_shader = new Shader("shaders/player_skin.vert","shaders/player_skin.frag",pt4,pn4,13);

	//Test static model shader
	GLuint pt5[] =
	{
		Shader::PARAM_VERTICES,
		Shader::PARAM_VERT_UV1,
		Shader::PARAM_VERT_UV2,
		Shader::PARAM_VERT_NORMALS,
		Shader::PARAM_MVP_MATRIX,
		Shader::PARAM_M_IT_MATRIX,
		Shader::PARAM_COLOR_MULT
	};
	const char *pn5[] =
	{
		"vert_pos",
		"vert_uv_1",
		"vert_uv_2",
		"vert_nor",
		"mvp",
		"m_IT",
		"color"
	};
	static_color_shader = new Shader("shaders/static_color.vert","shaders/static_color.frag",pt5,pn5,7);


	//Solid shader (draws as fullbright single color)
	//Test shader
	GLuint pt6[] =
	{
		Shader::PARAM_VERTICES,
		Shader::PARAM_MVP_MATRIX,
		Shader::PARAM_COLOR_ADD
	};
	const char *pn6[] =
	{
		"vert_pos",
		"mvp",
		"color"
	};
	solid_shader= new Shader("shaders/solid_color.vert","shaders/solid_color.frag",pt6,pn6,3);


	return 1;
}
void Game::unload_shaders ()
{
	delete test_shader;
	delete skel_color_shader;
	delete static_color_shader;
	delete text_shader;
	delete player_skin_shader;
	delete solid_shader;
}

int Game::load_materials()
{
	mat_red = new Material();
	mat_blue = new Material();
	skel_color_mat = new Material();
	static_color_mat = new Material();
	text_mat = new Material();
	player_skin_mat = new Material();
	solid_mat = new Material();

	return 1;
}
void Game::unload_materials()
{
	delete mat_red;
	delete mat_blue;
	delete skel_color_mat;
	delete text_mat;
	delete player_skin_mat;
	delete solid_mat;
}

int Game::load_textures()
{
	test_texture = new Texture("tex.pkm",512,512);
	char_set = new Texture("char_set.pkm",2048,2048);
	tex_arm_nor = new Texture("textures/arm_nor.pkm",1024,1024);
	tex_arm_diff = new Texture("textures/arm_diff.pkm",1024,1024);
	test_cube_map = new Cube_Map("cube_maps/test_cube_map.pkm",512);
	return 1;
}
void Game::unload_textures()
{
	delete test_texture;
	delete char_set;
	delete tex_arm_nor;
	delete tex_arm_diff;
	delete test_cube_map;
}

int Game::load_models()
{
	test_arms = new Skel_Model("models/test_arms.skmf");

	model_prim_cube = new Static_Model("models/primitive_cube.stmf");
	model_prim_quad = new Static_Model("models/primitive_quad.stmf");

	test_model_int_empty = new Static_Model("models/tiles/style0/empt0.stmf");

	player_skel = new Skeleton("animations/player_skeleton.sksf");
	player_skel->load_animation("animations/run.skaf");
	player_skel->load_animation("animations/speed_vault.skaf");
	player_skel->load_animation("animations/run_jump.skaf");
	player_skel->load_animation("animations/showcase_hands.skaf");

	skybox = new Skybox();
	return 1;
}
void Game::unload_models()
{
	delete test_arms;

	delete model_prim_cube;
	delete model_prim_quad;

	delete test_model_int_empty;

	delete player_skel;

	delete skybox;
}

int Game::load_sounds()
{
	test_pulse = new Sound_Sample("sounds/test_audio_pulse.raw");
	return 1;
}
void Game::unload_sounds()
{
	delete test_pulse;
}

int Game::load_assets()
{
	if(!Global_Tiles::init_data())
		return 0;
	if(!load_textures())
		return 0;
	if(!load_shaders())
		return 0;
	if(!load_materials())
		return 0;
	if(!load_models())
		return 0;
	if(!load_sounds())
		return 0;
	return 1;
}
void Game::unload_assets()
{
	unload_sounds();
	unload_models();
	unload_materials();
	unload_shaders();
	unload_textures();
	Global_Tiles::term_data();
}
//=================================================================================================
//Initialize GL aspects of all assets
int Game::init_gl()
{
	//=================================== Initializing shaders ====================================
	test_shader->init_gl();
	text_shader->init_gl();
	skel_color_shader->init_gl();
	player_skin_shader->init_gl();
	static_color_shader->init_gl();
	solid_shader->init_gl();

	//==================================== Loading textures =======================================
	test_texture->init_gl();
	char_set->init_gl();
	tex_arm_nor->init_gl();
	tex_arm_diff->init_gl();
	test_cube_map->init_gl();
	//==================================== Setting up Mesh VBOs ====================================
	test_arms->init_gl();
	model_prim_cube->init_gl();
	model_prim_quad->init_gl();

	test_model_int_empty->init_gl();

	skybox->init_gl();

	Global_Tiles::init_gl();

	glLineWidth(4.0f);

	return 1;
}

void Game::term_gl()
{
	//Terminating all loaded shaders
	player_skin_shader->term_gl();
	test_shader->term_gl();
	skel_color_shader->term_gl();
	static_color_shader->term_gl();
	text_shader->term_gl();
	solid_shader->term_gl();

	//Terminating all loaded models
	test_arms->term_gl();
	model_prim_cube->term_gl();
	model_prim_quad->term_gl();

	test_model_int_empty->term_gl();

	skybox->term_gl();

	Global_Tiles::term_gl();

	//Terminating all loaded textures
	test_cube_map->term_gl();
	tex_arm_nor->term_gl();
	tex_arm_diff->term_gl();
	char_set->term_gl();
	test_texture->term_gl();
}

void Game::handle_input(float x, float y, int event, int pointer_id)
{
	y = 1.0f - y;

	//Only do general stuff for other pointers, not 0th one
	//	(more complex input handling for 0th pointer is done below)
	//		(the handling for the 0th pointer also includes this general stuff)
	if(pointer_id != 0)
	{
		//General input handling stuff:
		if(event == INPUT_EVENT_ON_TOUCH_DOWN)
		{
			input_touching[pointer_id] = true;
			input_x[pointer_id] = x;
			input_y[pointer_id] = y;
			input_start_x[pointer_id] = x;
			input_start_y[pointer_id] = y;
		}
		if(event == INPUT_EVENT_ON_TOUCH_MOVE)
		{
			input_x[pointer_id] = x;
			input_y[pointer_id] = y;
		}
		if(event == INPUT_EVENT_ON_TOUCH_RELEASE)
		{
			input_x[pointer_id] = 0.0f;
			input_y[pointer_id] = 0.0f;
			input_start_x[pointer_id] = 0.0f;
			input_start_y[pointer_id] = 0.0f;
			input_touching[pointer_id] = false;
		}
		return;
	}

	//TODO: handle gamestates such as menu / pause menu

	if(event == INPUT_EVENT_ON_TOUCH_DOWN)
	{
		input_turning = false;
		input_sent_command = false;
		input_touching[0] = true;
		input_start_x[0] = x;
		input_start_y[0] = y;
	}
	else if(event == INPUT_EVENT_ON_TOUCH_RELEASE)
	{
		input_turning = false;
		input_sent_command = false;
		input_touching[0] = false;
		input_x[0] = 0.0f;
		input_y[0] = 0.0f;
		input_start_x[0] = 0.0f;
		input_start_y[0] = 0.0f;
		return;
	}

	switch(event)
	{
		case INPUT_EVENT_ON_TOUCH_DOWN:
		case INPUT_EVENT_ON_TOUCH_MOVE:
		case INPUT_EVENT_ON_TOUCH_RELEASE:
			input_x[0] = x;
			input_y[0] = y;
			break;
		default:
			break;
	}

	input_turn = 0;
	input_swipe = 0;

	if(input_sent_command)
		return;

	float delta_x = input_x[0] - input_start_x[0];
	float delta_y = input_y[0] - input_start_y[0];
	float delta_x_abs = fabsf(delta_x);
	float delta_y_abs = fabsf(delta_y);

	//Check if we are swiping horizontally or already turning
	if(input_turning || ((delta_x_abs > delta_y_abs) && (delta_x_abs > input_sensitivity)))
	{
		//if input_sensitivity is 1/16, the 16.0f and it annihilate each other
		//Making us only have to swipe 1/3rd of the screen width to go through the full range of motion
		input_turn = 3.0f * 16.0f * delta_x * input_sensitivity;
		input_turn = fmaxf(-1.0f,fminf(1.0f,input_turn));

		input_turning = true;
		return;
	}

	//Check if we are swiping vertically
	if(delta_y_abs > delta_x_abs)
	{
		if(delta_y > input_sensitivity*screen_ratio)
		{
			input_swipe = INPUT_SWIPE_UP;
			input_sent_command = true;
		}
		if(delta_y < -input_sensitivity*screen_ratio)
		{
			input_swipe = INPUT_SWIPE_DOWN;
			input_sent_command = true;
		}
		return;
	}
}


//Ran on first frame
//This is where we set up our game objects and their relationships
void Game::start()
{
	camera = new Camera();
	player = new Player();
	cam_to_bone = new Entity_Bone_Joint();
	test_sound_source = new Entity();

	//===== Setting up relationships between game objects ======
	audio_listener = camera;

	//Setting run anim as default anim
	player_skel->set_default_anim(0,Skeleton::END_TYPE_LOOP);
	player->mat = player_skin_mat;
	test_arms->skel = player_skel;

	//============================= Setting up materials ================================
	mat_red->set_shader(test_shader);
	mat_blue->set_shader(test_shader);
	text_mat->set_shader(text_shader);
	skel_color_mat->set_shader(skel_color_shader);
	static_color_mat->set_shader(static_color_shader);
	player_skin_mat->set_shader(player_skin_shader);
	solid_mat->set_shader(solid_shader);

	player_skin_mat->set_fixed_shader_param_ptr(Shader::PARAM_TEXTURE_NORMAL,(void*) tex_arm_nor);
	player_skin_mat->set_fixed_shader_param_ptr(Shader::PARAM_TEXTURE_DIFFUSE,(void*) tex_arm_diff);

	//Setting up fixed shader parameters
	float temp_color[] = {1.0f, 1.0f, 0.0f, 1.0f};
	static_color_mat->set_fixed_shader_param(Shader::PARAM_COLOR_MULT,temp_color,sizeof(float)*4);
	float temp_color_red[] = {1.0f, 0.4f, 0.4f, 1.0f};
	mat_red->set_fixed_shader_param(Shader::PARAM_TEST_FIELD, temp_color_red, sizeof(float) * 4);
	mat_red->set_fixed_shader_param_ptr(Shader::PARAM_TEXTURE_DIFFUSE, (void*) test_texture);
	float temp_color_blue[] = {0.4f, 0.4f, 1.0f, 1.0f};
	mat_blue->set_fixed_shader_param(Shader::PARAM_TEST_FIELD, temp_color_blue, sizeof(float) * 4);

	//===================================================================================

	skybox->set_cube_map(test_cube_map);

	test_sound_source->model = model_prim_cube;
	test_sound_source->mat = static_color_mat;


	//===== Instantiating Game Objects =====
	test_text = new UI_Text(text_mat,char_set);
	//Setting default text mat/shader/charset tex
	UI_Text::set_default_values(text_mat,char_set);
	//test_text->set_text("test\nT  E\n\nST !@\n#$%^&*()");
	//test_text->set_text("Pause\npause\nPAUSE\n\nPlay\nplay\nPLAY\n\nExit\nexit\nEXIT\n\ntest_text->set_text(\"Stuff\")");
	test_text->set_text(" ");
	//Place in top leftish corner
	test_text->pos.x = -screen_width * 0.4f;
	test_text->pos.y = screen_height * 0.4f;


	test_img = new UI_Image(text_mat,test_texture);
	test_img->pos.x = screen_width*0.5f - 100.0f;
	test_img->pos.y = screen_height*0.5f - 100.0f;
	test_img->scale.x = 200.0f;
	test_img->uv_maxs.x = 0.6f;
	test_img->uv_mins.y = 0.5f;
	test_img->maintain_aspect_ratio = true;

	player->player_model = test_arms;
	player->skel = player_skel;

	camera->parent = cam_to_bone;
	cam_to_bone->parent_skel = player_skel;
	cam_to_bone->parent_bone_index = 8; //head bone is at index 8, we could add methods for finding the bone
	// but we don't need all of that at the moment (since we are never going to parent anything to any other bone)
	player_skel->parent = player;
	player_skel->pos.z = 1.0f;
	camera->set_persp_view(90.0f * DEG_TO_RAD, screen_width,screen_height, 0.01f, 1000.0f);
	camera->set_ortho_view(screen_width,screen_height,0.0001f,1.0f);

	//Evaluating player bounding box triangle constants
	player_bbox_tri_slope = tanf((90.0f - PLAYER_MAX_TURN_ANGLE) * DEG_TO_RAD);
	player_bbox_tri_height = player_bbox_tri_slope * PLAYER_SIZE;


	//Start of game logic code
	buildings = new Building*[MAX_BUILDINGS];

	for(int i = 0; i < MAX_BUILDINGS; i++)
	{
		buildings[i] = new Building();
	}

	buildings[0]->generate();

	current_building = buildings[0];

	player->pos.y = 1;
	player_state = PLAYER_STATE_NOCLIP;
}

//Ran on last frame
//This is where we destroy our game objects
void Game::finish()
{
	int max = 5;

	for(int i = 0; i < MAX_BUILDINGS; i++)
	{
		buildings[i]->clear();
		delete buildings[i];
	}

	Global_Tiles::term_data();

	delete[] buildings;
	delete test_text;
	delete test_img;

	delete player;
	delete test_sound_source;
	delete camera;
	delete cam_to_bone;
}

//==== Game logic methods =====

//Draws player bounding box
void Game::draw_player_bbox(Mat4 vp)
{
	//Drawing bounding box
	const float bounding_box[] =
	{
		//Box portion
		//Bottom of box
		-PLAYER_SIZE,-PLAYER_SIZE,0.0f,	-PLAYER_SIZE,PLAYER_SIZE,0.0f,
		-PLAYER_SIZE,PLAYER_SIZE,0.0f,	PLAYER_SIZE,PLAYER_SIZE,0.0f,
		PLAYER_SIZE,PLAYER_SIZE,0.0f,		PLAYER_SIZE,-PLAYER_SIZE,0.0f,
		PLAYER_SIZE,-PLAYER_SIZE,0.0f,	-PLAYER_SIZE,-PLAYER_SIZE,0.0f,
		//Top of box
		-PLAYER_SIZE,-PLAYER_SIZE,2.0f,	-PLAYER_SIZE,PLAYER_SIZE,2.0f,
		-PLAYER_SIZE,PLAYER_SIZE,2.0f,	PLAYER_SIZE,PLAYER_SIZE,2.0f,
		PLAYER_SIZE,PLAYER_SIZE,2.0f,		PLAYER_SIZE,-PLAYER_SIZE,2.0f,
		PLAYER_SIZE,-PLAYER_SIZE,2.0f,	-PLAYER_SIZE,-PLAYER_SIZE,2.0f,
		//Corners of box
		-PLAYER_SIZE,-PLAYER_SIZE,0.0f,	-PLAYER_SIZE,-PLAYER_SIZE,2.0f,
		-PLAYER_SIZE,PLAYER_SIZE,0.0f,	-PLAYER_SIZE,PLAYER_SIZE,2.0f,
		PLAYER_SIZE,PLAYER_SIZE,0.0f,		PLAYER_SIZE,PLAYER_SIZE,2.0f,
		PLAYER_SIZE,-PLAYER_SIZE,0.0f,	PLAYER_SIZE,-PLAYER_SIZE,2.0f,

		//Triangle portion
		//Bottom of triangle
		-PLAYER_SIZE,PLAYER_SIZE,0.0f,	0.0f,PLAYER_SIZE+player_bbox_tri_height,0.0f,
		PLAYER_SIZE,PLAYER_SIZE,0.0f,		0.0f,PLAYER_SIZE+player_bbox_tri_height,0.0f,
		//Top of triangle
		-PLAYER_SIZE,PLAYER_SIZE,2.0f,	0.0f,PLAYER_SIZE+player_bbox_tri_height,2.0f,
		PLAYER_SIZE,PLAYER_SIZE,2.0f,		0.0f,PLAYER_SIZE+player_bbox_tri_height,2.0f,
		//Edge of triangle
		0.0f,PLAYER_SIZE+player_bbox_tri_height,0.0f,	0.0f,PLAYER_SIZE+player_bbox_tri_height,2.0f,
	};

	solid_mat->bind_material();
	Mat4 bbox_pos = vp * Mat4::TRANSLATE(player->pos);
	solid_mat->bind_value(Shader::PARAM_MVP_MATRIX,(void*) bbox_pos.m);//TODO: get player pos

	float color[] = {0.0f,1.0f,0.0f,1.0f};
	solid_mat->bind_value(Shader::PARAM_VERTICES,(void*) bounding_box);
	solid_mat->bind_value(Shader::PARAM_COLOR_ADD,(void*) color);
	glDrawArrays(GL_LINES, 0, 34);
}
//Draws active floors collision voxels
void Game::draw_floor_collision_voxels(Mat4 vp)
{
	Vec3 building_org = current_building->active_floor->global_mins + Vec3(0,0,0.5f)*GRID_SIZE;
	Vec3 tile_pos;
	Vec3 voxel_pos;
	char voxel_rank;

	const float voxel_box[] =
	{
	//Top of box
	0,0,GRID_SIZE,		0,GRID_SIZE,GRID_SIZE,
	0,0,GRID_SIZE,		GRID_SIZE,0,GRID_SIZE,

	//Box x
	0,0,GRID_SIZE,			GRID_SIZE,GRID_SIZE,GRID_SIZE,
	GRID_SIZE,0,GRID_SIZE,	0,GRID_SIZE,GRID_SIZE,
	};

	solid_mat->bind_material();
	solid_mat->bind_value(Shader::PARAM_VERTICES,(void*) voxel_box);
	Mat4 vox_trans;

	for(int i = 0; i < current_building->active_floor->width; i++)
	{
		for(int j = 0; j < current_building->active_floor->length; j++)
		{
			tile_pos = building_org + Vec3(i*TILE_SIZE,j*TILE_SIZE,0.0f);
			for(int k = 0; k < TILE_VOXEL_DIMS; k++)
			{
				for(int l = 0; l < TILE_VOXEL_DIMS; l++)
				{
					voxel_rank = current_building->active_floor->tile_coll_map[i][j]->get_vox_at(k,l);

					if(voxel_rank == 0)
					{
						continue;
					}
					if(voxel_rank == 1)
					{
						float color[] = {0.75f,0.25f,0.25f,1.0f};
						solid_mat->bind_value(Shader::PARAM_COLOR_ADD,(void*) color);
					}
					voxel_pos = tile_pos + Vec3(k*GRID_SIZE,l*GRID_SIZE,0.0f);
					vox_trans = vp * Mat4::TRANSLATE(voxel_pos);
					solid_mat->bind_value(Shader::PARAM_MVP_MATRIX,(void*) vox_trans.m);
					glDrawArrays(GL_LINES, 0, 8);
				}
			}
		}
	}
}
//Draws active floors maneuver data
void Game::draw_floor_maneuvers(Mat4 vp)
{
	//TODO
}
//Returns the pos if in mins & maxs, otherwise caps to lie within the mins & maxs
Vec3 Game::cap_to_bounds(Vec3 pos, Vec3 mins, Vec3 maxs)
{
	Vec3 result = pos;
	//Check x-axis
	if(result.x <= mins.x)
		result.x = mins.x;
	else if(result.x >= maxs.x)
		result.x = maxs.x;
	//Check y-axis
	if(result.y <= mins.y)
		result.y = mins.y;
	else if(result.y >= maxs.y)
		result.y = maxs.y;
	//Check z-axis
	if(result.z <= mins.z)
		result.z = mins.z;
	else if(result.z >= maxs.z)
		result.z = maxs.z;

	return result;
}

void Game::mnvr_movement ()
{
	//TODO: maneuver logic
}

void Game::reached_mnvr_keyframe ()
{
	//TODO: handle traversing logic
	//Setting up movement for keyframe:
	//Checking if we are done with the animation
	if(mnvr_frame_number >= mnvr_current->keyframe_count - 1)
	{
		player_state = PLAYER_STATE_RUNNING;
		mnvr_current = NULL;
		mnvr_frame = NULL;
		mnvr_frame_number = 0;
	}
	else
	{
		mnvr_frame = mnvr_current->keyframes[++mnvr_frame_number];
		mnvr_start_pos = cap_to_bounds(player->pos, mnvr_frame->mins, mnvr_frame->maxs);
		//TODO: how do we get goal position of the next maneuver keyframe?
		//mnvr_goal_pos = cap_to_bounds(player->pos, mnvr_current->keyframes[mnvr_frame_number+1]->mins,mnvr_current->keyframes[mnvr_frame_number+1]->maxs);

	}
}

//TODO: handle precedence of collisions
//Returns type of collision player bbox encounters
char Game::clip_player_bbox(Vec3 p)
{
	//check for collisions at certain points
	//We need global positions for certain coords

	Vec3 pos = p;

	char result;

	//Front of triangle
	float rcorner_cmpr = -player_bbox_tri_slope * (efmodf(pos.x,GRID_SIZE)) + GRID_SIZE;
	float lcorner_cmpr = player_bbox_tri_slope * (efmodf(pos.x,GRID_SIZE) - GRID_SIZE) + GRID_SIZE;

	float mod_y = efmodf(pos.y,GRID_SIZE);
	if(mod_y >= lcorner_cmpr)
	{
		//Check front left voxel
		result = current_building->is_solid_at(pos + Vec3(-PLAYER_SIZE,PLAYER_SIZE + GRID_SIZE,0));
		if(result != 0)
			return result;

	}
	if(mod_y >= rcorner_cmpr)
	{
		//Check front right voxel
		result = current_building->is_solid_at(pos + Vec3(PLAYER_SIZE,PLAYER_SIZE + GRID_SIZE,0));
		if(result != 0)
			return result;
	}

	result = current_building->is_solid_at(pos + Vec3(0,PLAYER_SIZE + player_bbox_tri_height,0));
	if(result != 0)
		return result;

	//Front right
	result = current_building->is_solid_at(pos + Vec3(PLAYER_SIZE,PLAYER_SIZE,0));
	if(result != 0)
		return result;

	//Front left
	result = current_building->is_solid_at(pos + Vec3(-PLAYER_SIZE,PLAYER_SIZE,0));
	if(result != 0)
		return result;

	//Mid right
	result = current_building->is_solid_at(pos + Vec3(PLAYER_SIZE,0,0));
	if(result != 0)
		return result;
	//Mid left
	result = current_building->is_solid_at(pos + Vec3(-PLAYER_SIZE,0,0));
	if(result != 0)
		return result;

	//back right
	result = current_building->is_solid_at(pos + Vec3(PLAYER_SIZE,-PLAYER_SIZE,0));
	if(result != 0)
		return result;

	//back left
	result = current_building->is_solid_at(pos + Vec3(-PLAYER_SIZE,-PLAYER_SIZE,0));
	if(result != 0)
		return result;

	//Back center
	result = current_building->is_solid_at(pos + Vec3(0,-PLAYER_SIZE,0));
	if(result != 0)
		return result;

	return 0;
	//TODO: make precedence array for which collision type takes higher precedence, we only return the clip type that has the highest precedence
}

//returns true if move was succesfull, returns false if we collided with something and set state to DEAD
bool Game::move_player(Vec3 v)
{
	//Split up movement into forward, sideways, and vertical movement
	float delta_y = v.y * Time::delta_time;
	float delta_x = v.x * Time::delta_time;
	float delta_z = v.z * Time::delta_time;

	//Checking forward collisions
	Vec3 forward_pos = player->pos + Vec3(0,delta_y,0);

	char clip = clip_player_bbox(forward_pos);

	if(clip == 0)
	{
		player->pos.y = forward_pos.y;
	}
	else
	{
		//TODO: we collided! handle death
	}

	//Checking sideways collisions
	Vec3 side_pos = player->pos + Vec3(delta_x,0,0);



	clip = clip_player_bbox(side_pos);

	if(clip == 0)
	{
		player->pos.x = side_pos.x;
	}
	else
	{
		//TODO: we collided! handle death
	}

	//Don't do collision detection in z-axis (we let PLAYER_STATE_FALLING logic handle that)
	player->pos.z += delta_z;

	return true;
}

void Game::update()
{
	//if(state.x > 0.95f && player_skel->playing_anim)
	//	player_skel->stop_anim();

	static bool played_anim = false;
	if(!played_anim)
	{
		played_anim = true;
		//player_skel->play_anim(3,Skeleton::END_TYPE_DEFAULT_ANIM); 3 is showcase hands
		player_skel->play_anim(0,Skeleton::END_TYPE_LOOP);
	}



	//====Test show/hide ad calls====
	static bool ad_visible = false;
	if(input_x[4] < 0.10f && input_touching[4] && ad_visible)
	{
		//jnii->hide_ad();
		jnii->hide_keyboard();
		ad_visible = false;
	}
	else if(input_x[4] > 0.90f && input_touching[4] && !ad_visible)
	{
		//jnii->show_ad();
		jnii->show_keyboard();
		ad_visible = true;
	}
	//============================


	float t = Time::time();

	//Making the test audio source move / rotate
	float distance = 5.0f;
	test_sound_source->pos = Vec3(distance * cosf(0.5f*t),distance * sinf(0.5f*t),0.0f);
	test_sound_source->angles.y = fmodf(t*8.0f,TWO_PI);


	//=========== Test Audio Playing every 0.5 seconds ==============
	static float time_to_play_audio = 0.0f;
	if(t > time_to_play_audio)
	{
		time_to_play_audio = t + 0.5f;
		test_sound_source->play_sound(test_pulse);
	}

	//player->angles.y = -(input_x-0.5f)*TWO_PI;
	//player->angles.x = (input_y-0.5f)*PI;

	if(player_state == PLAYER_STATE_NOCLIP || player_state == PLAYER_STATE_CAM_FLY)
	{
		//zones:
		//look left/right/up/down
		//move left/right/forward/back
		//move up/down


		//Camera velocity
		float cam_vel = 60.0f;

		//Camera angular velocity
		float cam_ang_vel = 140.0f * DEG_TO_RAD;

		Entity* move_ent = NULL;

		if(player_state == PLAYER_STATE_NOCLIP)
			move_ent = player;
		else
			move_ent = camera;

		//Checking input from all fingers:
		for(int i = 0; i < MAX_INPUT_TOUCHES; i++)
		{
			if(!(input_touching[i]))
				continue;
			float x = input_x[i];
			float y = input_y[i];

			float sx = input_start_x[i];
			float sy = input_start_y[i];

			//top right corner: go back to player run mode
			if(sx >= 0.66f)
			{
				if(sy >= 0.85f)
				{
					input_touching[i] = false;
					if(player_state == PLAYER_STATE_NOCLIP)
					{
						player_state = PLAYER_STATE_CAM_FLY;
						player->angles = Vec3::ZERO();
						if(player->pos.z <= current_building->active_floor->altitude)
						{
							player->pos.z = current_building->active_floor->altitude+0.01f;
						}
						if(player->pos.x >= current_building->active_floor->global_maxs.x - 0.5f)
						{
							player->pos.x = current_building->active_floor->global_maxs.x - 1.0f;
						}
						if(player->pos.x <= current_building->active_floor->global_mins.x + 0.5f)
						{
							player->pos.x = current_building->active_floor->global_mins.x + 1.0f;
						}

						if(player->pos.y <= current_building->active_floor->global_mins.y + 0.5f)
						{
							player->pos.y = current_building->active_floor->global_mins.y + 1.0f;
						}
						return;
					}
					else
					{
						player_state = PLAYER_STATE_RUNNING;
						return;
					}
				}
			}
			//top left corner
			if(sx <= 0.33f)
			{
				if(sy >= 0.85f)
				{
					//Test collision
					if(player_state == PLAYER_STATE_NOCLIP)
					{
						input_touching[i] = false;
						move_player(Vec3::ZERO());
					}
					//Reset camera offset
					if(player_state == PLAYER_STATE_CAM_FLY)
					{
						camera->pos = Vec3::ZERO();
						camera->angles = Vec3::ZERO();
					}
				}
			}

			//bottom third right half is camera view direction
			if(sx > 0.5f)
			{
				if(sy < 0.33f)
				{
					//float delta_y = fmaxf(fminf((y - 0.165f) / 0.17f,1.0f),-1.0f);//measured from area center
					float delta_y = fmaxf(fminf((y - sy) / 0.17f,1.0f),-1.0f);//measured from touch start pos
					//float delta_x = -1.0f * fmaxf(fminf((x - 0.75f) / 0.25f,1.0f),-1.0f);//measured from area center
					float delta_x = -1.0f * fmaxf(fminf((x - sx) / 0.25f,1.0f),-1.0f);//measured from touch start pos
					delta_x *= cam_ang_vel;
					delta_y *= cam_ang_vel;
					move_ent->angles.x += delta_y * Time::delta_time;
					move_ent->angles.y += delta_x * Time::delta_time;
					continue;
				}
			}
			//bottom third left half is camera movement
			if(sx < 0.5f)
			{
				if(sy < 0.33f)
				{
					//float delta_y = fmaxf(fminf((y - 0.165f) / 0.17f,1.0f),-1.0f);//measured from area center
					float delta_y = fmaxf(fminf((y - sy) / 0.17f,1.0f),-1.0f);//measured from touch start pos
					//float delta_x = fmaxf(fminf((x - 0.25f) / 0.25f,1.0f),-1.0f);//measured from area center
					float delta_x = fmaxf(fminf((x - sx) / 0.25f,1.0f),-1.0f);//measured from touch start pos
					delta_x *= cam_vel;
					delta_y *= cam_vel;
					Vec3 forward, right, up;
					move_ent->angles.angles_to_dirs(&forward,&right,&up);
					move_ent->pos = move_ent->pos + (forward * delta_y * Time::delta_time) + (right * delta_x * Time::delta_time);
					continue;
				}
			}

			//second third left half is camera height
			if(sx < 0.5f)
			{
				if(sy >= 0.33f && sy < 0.66f)
				{
					//float delta_y = fminf((y - 0.5f) / 0.17f,1.0f);//measured from area center
					float delta_y = fminf((y - sy) / 0.17f,1.0f);//measured from touch start pos
					delta_y *= cam_vel;
					Vec3 forward, right, up;
					move_ent->angles.angles_to_dirs(&forward,&right,&up);
					move_ent->pos = move_ent->pos + (up * delta_y * Time::delta_time);
					continue;
				}
			}
		}

		return;
	}

	//FIXME: remove this
	//TODO: handle input here
	//TODO: check for maneuvers and traversals
	//Checking touch button interactions
	//Checking input from all fingers:
	for(int i = 0; i < MAX_INPUT_TOUCHES; i++)
	{
		if(!(input_touching[i]))
			continue;
		float x = input_start_x[i];
		float y = input_start_y[i];

		//top right corner: go to player noclip mode
		if(x >= 0.66f && y >= 0.85f)
		{
			player_state = PLAYER_STATE_NOCLIP;
			input_touching[i] = false;
			player->angles.x = 0.0f;
			player->angles.y = 0.0f;
			player->angles.z = 0.0f;
			camera->viewbob_angles = Vec3::ZERO();
			camera->viewbob_vel = Vec3::ZERO();
			return;
		}
		//For toggling viewbob edit menu
		if(x <= 0.33f && y >= 0.85f)
		{
			input_touching[i] = false;
			viewbob_menu_state++;
			if(viewbob_menu_state >= 3)
				viewbob_menu_state = 0;
			continue;
		}
		//For zeroing out the viewbob
		if(x > 0.33f && x < 0.66f && y >= 0.85f)
		{
			input_touching[i] = false;

			camera->viewbob_vel = Vec3::ZERO();
			camera->angles = Vec3::ZERO();
		}

		//left 10% = 0, right 10% = 1.0
		float clipped_x = fmaxf(fminf((x-0.1f)/0.8f,1.0f),0.0f);
		//Altering run viewbob values
		if(viewbob_menu_state == 1)
		{
			//range is [0-100]
			//Edit top field
			if(y > 0.72 && y < 0.80)
			{
				viewbob_pitch = 100 * clipped_x;
				continue;
			}
			//Edit middle field
			if(y > 0.64 && y < 0.72)
			{
				viewbob_yaw = 100 * clipped_x;
				continue;
			}
			//Edit bottom field
			if(y > 0.56 && y < 0.64)
			{
				viewbob_roll = 100 * clipped_x;
				continue;
			}
		}
		//Altering camera parameters
		if(viewbob_menu_state == 2)
		{
			//Edit top field
			if(y > 0.72 && y < 0.80)
			{
				//due to massive range, I want this to be on a cubic scale
				camera->viewbob_spring_constant = 10000 * clipped_x * clipped_x * clipped_x;
				continue;
			}
			//Edit middle field
			if(y > 0.64 && y < 0.72)
			{
				//I want this to be on a cubic scale as well
				camera->viewbob_resistance = 10 * clipped_x * clipped_x * clipped_x;
				continue;
			}
			//Edit bottom field
			if(y > 0.56 && y < 0.64)
			{
				camera->viewbob_max_stray = 90 * clipped_x;
				continue;
			}
		}
	}

	if(player_state == PLAYER_STATE_RUNNING)
	{
		//Get Maneuvers that require no input

		//TODO: check for traversals as well
		Maneuver* man = current_building->input_to_maneuver(player->pos,INPUT_SWIPE_NONE);

		if(man)
		{
			player_state = PLAYER_STATE_MANEUVERING;
			mnvr_current = man;
			mnvr_tile_ofs = current_building->get_tile_ofs_at_pos(player->pos);
			mnvr_frame_number = 0;
			mnvr_frame = man->keyframes[0];
			reached_mnvr_keyframe();
		}

		if(input_swipe)
		{
			//Get maneuvers that require input up
			if(input_swipe == INPUT_SWIPE_UP)
			{
				//TODO: if not in maneuver area, generic jump
				player_state = PLAYER_STATE_FALLING;
				float jump_height = 0.75f;

				float jump_vel = sqrtf(jump_height * 2.0f * 9.8f);//9.8f is gravity

				player_phys_vel.z = jump_vel;
				player_phys_vel = player_phys_vel + (Quat(player->angles.y,Vec3::UP()) * Vec3(0,player_runspeed,0));


				//TODO: play jump animation
				return;
			}
			//Get maneuvers that require input down
			if(input_swipe == INPUT_SWIPE_DOWN)
			{
				//player_state == PLAYER_STATE_SLIDING;
				//TODO: if not in maneuver area, generic slide
			}

		}
		//TODO: put this frame handling stuff in a different location
		//==============================================================
		if(player_skel->playing_anim)
		{
			if(player_skel->current_anim == 0)
			{
				if(player_skel->current_frame == 9)//left foot hit ground
				{
					//TODO: play footstep sounds
					//camera->viewbob_run_footstep(-5.0f*DEG_TO_RAD,2.0f*DEG_TO_RAD,0.0f);
					//test viewbob: no pitch bob, only yaw and roll
					//camera->viewbob_run_footstep(0.0f,2.0f*DEG_TO_RAD,5.0f*DEG_TO_RAD);
					camera->viewbob_run_footstep(-viewbob_pitch*DEG_TO_RAD,viewbob_yaw*DEG_TO_RAD,viewbob_roll*DEG_TO_RAD);
				}
				if(player_skel->current_frame == 24)//right foot hit ground
				{
					//camera->viewbob_run_footstep(-5.0f*DEG_TO_RAD,-2.0f*DEG_TO_RAD,0.0f);
					//test viewbob
					//camera->viewbob_run_footstep(0.0f,-2.0f*DEG_TO_RAD,-5.0f*DEG_TO_RAD);
					camera->viewbob_run_footstep(-viewbob_pitch*DEG_TO_RAD,-viewbob_yaw*DEG_TO_RAD,-viewbob_roll*DEG_TO_RAD);
				}
			}
		}
		//==============================================================

		camera->set_viewbob(Camera::VIEWBOB_RUNNING);


		//Testing viewbob code
		static bool stepped = true;

		if(input_y[1] <= 0.1f && !stepped)
		{
			stepped = true;
			if(input_x[1] > 0.5f)
			{
				camera->viewbob_run_footstep(-50.0f*DEG_TO_RAD,-50.0f*DEG_TO_RAD,0.0f);
			}
			else
			{
				camera->viewbob_run_footstep(-50.0f*DEG_TO_RAD,50.0f*DEG_TO_RAD,0.0f);
			}
		}
		else if(input_y[1] > 0.1f)
				stepped = false;
		//========================= end test viewbob code

		camera->update_viewbob();

		if(player->pos.z > current_building->active_floor->altitude)
		{
			player_state = PLAYER_STATE_FALLING;
			return;
		}

		//Player turning code:
		float turn_angle = 0.0f;
		if(input_turning)
		{
			turn_angle = -PLAYER_MAX_TURN_ANGLE * input_turn * DEG_TO_RAD;
		}
		player->angles.y += (turn_angle - player->angles.y) * 0.5f;
		//TODO: camera roll rotation from turning


		//Make the player move forward, if runs outside of building bounds, reset at building start
		Vec3 movement_vel = Quat(player->angles.y,Vec3::UP()) * Vec3(0,player_runspeed,0);

		if(!move_player(movement_vel))
			return;

		//player->pos = player->pos + Time::delta_time * movement_vel;
		if(current_building->is_box_out_of_bounds(player->pos,PLAYER_SIZE))//TODO: make 0.5f be the player size
		{
			player->pos = current_building->active_floor->global_pos + Vec3(0.0f,1.0f,0.0f);
		}

		//TODO: run logic
	}
	if(player_state == PLAYER_STATE_FALLING)
	{
		//TODO: slide logic
		Vec3 movement_vel;



		player_phys_vel.z += -9.8 * Time::delta_time;
		if(player_phys_vel.z < -40.0f)//terminal vel
			player_phys_vel.z = -40.0f;

		Vec3 delta_pos = Time::delta_time * player_phys_vel;

		if(player->pos.z + delta_pos.z < current_building->active_floor->altitude)
		{
			player_state = PLAYER_STATE_RUNNING;
			player->pos.z = current_building->active_floor->altitude;
			player_phys_vel = Vec3::ZERO();
			return;
		}
		player->pos = player->pos + delta_pos;
	}
	//TODO: other states


	//TODO: make this only execute at 30 times per second
	player->update();
}

//Draws the scene
void Game::render()
{
	//Setting all transforms to be recalculated
	player_skel->transform_calculated = false;
	camera->transform_calculated = false;
	player->transform_calculated = false;
	test_sound_source->transform_calculated = false;
	cam_to_bone->transform_calculated = false;

	//glClear(GL_COLOR_BUFFER_BIT);

	camera->update_view_matrix();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//Setting up global shader parameters
	//Time
	float t = Time::time();
	Shader::set_static_global_param(Shader::GLOBAL_PARAM_FLOAT_TIME,&t);
	//Camera direction
	float cam_dir[] = {camera->forward.x,camera->forward.y,camera->forward.z};
	Shader::set_static_global_param(Shader::GLOBAL_PARAM_VEC3_CAM_DIR, cam_dir);
	//Camera position
	float cam_pos[] = {camera->pos.x,camera->pos.y,camera->pos.z};
	Shader::set_static_global_param(Shader::GLOBAL_PARAM_VEC3_CAM_POS, cam_pos);
	//Directional light direction
	float light_dir[] = {0,0,-1};
	Shader::set_static_global_param(Shader::GLOBAL_PARAM_VEC3_DIRLIGHT_DIR, light_dir);
	//Directional light color
	float light_col[] = {1.0,0.0,0.0};
	Shader::set_static_global_param(Shader::GLOBAL_PARAM_VEC3_DIRLIGHT_COL, light_col);



	Mat4 vp = camera->persp_proj_m * camera->view_m;

	player->render(vp);
	Mat4 view_no_translation = camera->inf_proj_m * ((camera->view_m).pos_removed());

	buildings[0]->render(vp);

	skybox->render(view_no_translation);

	//Have to draw transparent objects after skybox
	test_sound_source->render(vp);

	buildings[0]->render_transparent_meshes(vp);


	//Test UI image
	test_img->render(camera->ortho_proj_m);

	//Test UI Text
	//char time_str[20];
	//snprintf(time_str,20,"t=%f",t);
	//test_text->set_text(time_str);

	if(player_state != PLAYER_STATE_NOCLIP && player_state != PLAYER_STATE_CAM_FLY)
	{
		//"Edit	Reset Vbob"
		if(viewbob_menu_state == 0)
		{
			char test_viewbob_str[40];
			snprintf(test_viewbob_str,40,"[Edit]\t[Zero]");
			test_text->set_text(test_viewbob_str);
		}
		if(viewbob_menu_state == 1)
		{
			char test_viewbob_str[120];
			snprintf(test_viewbob_str,120,"[Edit]\t[Zero]\n\nEdit run velocities\nPitch\n\t%.2f\nYaw\n\t%.2f\nRoll\n\t%.2f",viewbob_pitch,viewbob_yaw,viewbob_roll);
			test_text->set_text(test_viewbob_str);
		}
		if(viewbob_menu_state == 2)
		{
			char test_viewbob_str[120];
			snprintf(test_viewbob_str,120,"[Edit]\t[Zero]\n\nEdit cam properties\nSpring Constant\n\t%.2f\nResistance\n\t%.2f\nMax Stray\n\t%.2f",camera->viewbob_spring_constant,camera->viewbob_resistance,camera->viewbob_max_stray);
			test_text->set_text(test_viewbob_str);
		}
		//char test_viewbob_str[40];
		//snprintf(test_viewbob_str,40,"t=%f",t);
		//test_text->set_text(test_viewbob_str);
		test_text->render(camera->ortho_proj_m);
	}

	if(player_state == PLAYER_STATE_NOCLIP)
	{
		UI_Text::draw_text("Mode:\n NOCLIP", Vec3(-screen_width * 0.4f,screen_height * 0.45f,0.5f), Vec3(0,0,0), 100.0f, Vec3(1,1,1), Vec3(0,0,0), 1.0f, false, camera->ortho_proj_m);
	}
	if(player_state == PLAYER_STATE_CAM_FLY)
	{
		UI_Text::draw_text("Mode:\n CAM FLY", Vec3(-screen_width * 0.4f,screen_height * 0.45f,0.5f), Vec3(0,0,0), 100.0f, Vec3(1,1,1), Vec3(0,0,0), 1.0f, false, camera->ortho_proj_m);
	}

	draw_floor_collision_voxels(vp);
	draw_player_bbox(vp);
}