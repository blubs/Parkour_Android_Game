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
	player_torso_mat = new Material();
	player_leg_mat = new Material();
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
	delete player_torso_mat;
	delete player_leg_mat;
	delete solid_mat;
}

int Game::load_textures()
{
	test_texture = new Texture("tex.pkm",512,512);
	char_set = new Texture("char_set.pkm",2048,2048);
	tex_arm_nor = new Texture("textures/arm_nor.pkm",1024,1024);
	tex_arm_diff = new Texture("textures/arm_diff.pkm",1024,1024);
	tex_torso_nor = new Texture("textures/torso_nor.pkm",512,512);
	tex_torso_diff = new Texture("textures/torso_diff.pkm",512,512);
	tex_leg_nor = new Texture("textures/leg_nor.pkm",512,512);
	tex_leg_diff = new Texture("textures/leg_diff.pkm",512,512);
	return 1;
}
void Game::unload_textures()
{
	delete test_texture;
	delete char_set;
	delete tex_arm_nor;
	delete tex_arm_diff;
	delete tex_torso_nor;
	delete tex_torso_diff;
	delete tex_leg_nor;
	delete tex_leg_diff;
}

int Game::load_models()
{
	test_arms = new Skel_Model("models/test_arms.skmf");
	test_torso = new Skel_Model("models/test_torso.skmf");
	test_legs = new Skel_Model("models/test_legs.skmf");

	model_prim_cube = new Static_Model("models/primitive_cube.stmf");
	model_prim_quad = new Static_Model("models/primitive_quad.stmf");

	test_model_int_empty = new Static_Model("models/tiles/style0/empt0.stmf");

	player_skel = new Skeleton("animations/player_skeleton.sksf");

	//The order of loading these animations must match the animation identifiers
	player_skel->load_animation("animations/run.skaf");
	player_skel->load_animation("animations/speed_vault.skaf");
	player_skel->load_animation("animations/run_jump.skaf");
	player_skel->load_animation("animations/slide.skaf");
	player_skel->load_animation("animations/slide_end.skaf");
	player_skel->load_animation("animations/showcase_hands.skaf");
	//NOTE: any animation added here must also be added as an identifier in game_defs.hpp
	skybox = new Skybox();
	return 1;
}
void Game::unload_models()
{
	delete test_arms;
	delete test_torso;
	delete test_legs;

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
	tex_torso_nor->init_gl();
	tex_torso_diff->init_gl();
	tex_leg_nor->init_gl();
	tex_leg_diff->init_gl();
	//==================================== Setting up Mesh VBOs ====================================
	test_arms->init_gl();
	test_torso->init_gl();
	test_legs->init_gl();
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
	test_torso->term_gl();
	test_legs->term_gl();
	model_prim_cube->term_gl();
	model_prim_quad->term_gl();

	test_model_int_empty->term_gl();

	skybox->term_gl();

	Global_Tiles::term_gl();

	//Terminating all loaded textures
	tex_arm_nor->term_gl();
	tex_arm_diff->term_gl();
	tex_torso_diff->term_gl();
	tex_leg_diff->term_gl();
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
	if(input_turning || ((delta_x_abs > delta_y_abs) && (delta_x_abs > INPUT_SENSITIVITY)))
	{
		//if input_sensitivity is 1/16, the 16.0f and it annihilate each other
		//Making us only have to swipe 1/3rd of the screen width to go through the full range of motion
		input_turn = 3.0f * 16.0f * delta_x * INPUT_SENSITIVITY;
		input_turn = fmaxf(-1.0f,fminf(1.0f,input_turn));

		input_turning = true;
		return;
	}

	//Check if we are swiping vertically
	if(delta_y_abs > delta_x_abs)
	{
		if(delta_y > INPUT_SENSITIVITY*screen_ratio)
		{
			input_swipe = INPUT_SWIPE_UP;
			input_sent_command = true;
		}
		if(delta_y < - INPUT_SENSITIVITY*screen_ratio)
		{
			input_swipe = INPUT_SWIPE_DOWN;
			input_sent_command = true;
		}
		return;
	}
}

//Handles hardware back key / keyboard input
void Game::handle_key_input(int event_type, char event_key_char)
{
	if(event_type == INPUT_KEY_BACK)
	{
		//TODO: handle back key logic
		//TODO: handle the following situation:
		//TODO: 	if the keyboard is visible and back key is pressed, the keyboard is hidden
		LOGI("The back key has been pressed");
	}
	if(event_type == INPUT_KEY_KEYBOARD)
	{
		LOGI("Keyboard key pressed: (ascii value: %d) char: %c",event_key_char,event_key_char);
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
	player_skel->set_default_anim(0,ANIM_END_TYPE_LOOP);
	player->mat1 = player_skin_mat;
	player->mat2 = player_torso_mat;
	player->mat3 = player_leg_mat;

	test_arms->skel = player_skel;
	test_torso->skel = player_skel;
	test_legs->skel = player_skel;

	//============================= Setting up materials ================================
	mat_red->set_shader(test_shader);
	mat_blue->set_shader(test_shader);
	text_mat->set_shader(text_shader);
	skel_color_mat->set_shader(skel_color_shader);
	static_color_mat->set_shader(static_color_shader);
	player_skin_mat->set_shader(player_skin_shader);
	player_torso_mat->set_shader(player_skin_shader);
	player_leg_mat->set_shader(player_skin_shader);
	solid_mat->set_shader(solid_shader);

	player_skin_mat->set_fixed_shader_param_ptr(Shader::PARAM_TEXTURE_NORMAL,(void*) tex_arm_nor);
	player_skin_mat->set_fixed_shader_param_ptr(Shader::PARAM_TEXTURE_DIFFUSE,(void*) tex_arm_diff);

	player_torso_mat->set_fixed_shader_param_ptr(Shader::PARAM_TEXTURE_NORMAL,(void*) tex_torso_nor);
	player_torso_mat->set_fixed_shader_param_ptr(Shader::PARAM_TEXTURE_DIFFUSE,(void*) tex_torso_diff);

	player_leg_mat->set_fixed_shader_param_ptr(Shader::PARAM_TEXTURE_NORMAL,(void*) tex_leg_nor);
	player_leg_mat->set_fixed_shader_param_ptr(Shader::PARAM_TEXTURE_DIFFUSE,(void*) tex_leg_diff);

	//Setting up fixed shader parameters
	float temp_color[] = {1.0f, 1.0f, 0.0f, 1.0f};
	static_color_mat->set_fixed_shader_param(Shader::PARAM_COLOR_MULT,temp_color,sizeof(float)*4);
	float temp_color_red[] = {1.0f, 0.4f, 0.4f, 1.0f};
	mat_red->set_fixed_shader_param(Shader::PARAM_TEST_FIELD, temp_color_red, sizeof(float) * 4);
	mat_red->set_fixed_shader_param_ptr(Shader::PARAM_TEXTURE_DIFFUSE, (void*) test_texture);
	float temp_color_blue[] = {0.4f, 0.4f, 1.0f, 1.0f};
	mat_blue->set_fixed_shader_param(Shader::PARAM_TEST_FIELD, temp_color_blue, sizeof(float) * 4);

	//===================================================================================

	skybox->set_cube_map(Global_Tiles::instance->sky_cube_map);

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

	player->player_model1 = test_arms;
	player->player_model2 = test_torso;
	player->player_model3 = test_legs;
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

	buildings[0]->generate(NULL,Vec3::ZERO());
	//FIXME remove this:
	buildings[0]->active_floor->debug_branch_mat = solid_mat;

	//Distance between buildings
	Vec3 bldg_offset = Vec3(0,15,0);

	for(int i = 1; i < MAX_BUILDINGS; i++)
	{
		buildings[i]->generate(buildings[PREV_BLDG[i]],bldg_offset);
	}

	//Generate the first building's floor after we generate all of the buildings themselves
	buildings[0]->generate_floor(player->pos,buildings[1]);

	current_building = buildings[0];
	cbldg_index = 0;

	player->pos.y = 1;
	player_state = PLAYER_STATE_NOCLIP;
}

//Ran on last frame
//This is where we destroy our game objects
void Game::finish()
{
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

		//Axes at player position
		//X-axis
		0.0f,0.0f,0.0f,	0.25f,0.0f,0.0f,
		//Y-axis
		0.0f,0.0f,0.0f,	0.0f,0.25f,0.0f,
		//Z-axis
		0.0f,0.0f,0.0f,	0.0f,0.0f,0.25f,
	};

	solid_mat->bind_material();
	Mat4 bbox_pos = vp * Mat4::TRANSLATE(player->pos);
	solid_mat->bind_value(Shader::PARAM_MVP_MATRIX,(void*) bbox_pos.m);

	float color_green[] = {0.0f,1.0f,0.0f,1.0f};
	float color_red[] = {1.0f,0.0f,0.0f,1.0f};



	solid_mat->bind_value(Shader::PARAM_VERTICES,(void*) bounding_box);

	//Check if player is colliding:
	move_player(Vec3::ZERO());
	//player_colliding is updated by this call (which does nothing)
	if(!player_colliding)
		solid_mat->bind_value(Shader::PARAM_COLOR_ADD,(void*) color_green);
	else
		solid_mat->bind_value(Shader::PARAM_COLOR_ADD,(void*) color_red);
	glDrawArrays(GL_LINES, 0, 40);
}
//Draws active floor maneuver keyframes
void Game::draw_keyframe(Mat4 vp, Keyframe* key, Vec3 ofs)
{
	Vec3 mins = key->mins;
	Vec3 maxs = key->maxs;
	const float bounds[] =
	{
		//Bottom box
		mins.x,mins.y,mins.z,		mins.x,maxs.y,mins.z,
		mins.x,maxs.y,mins.z,		maxs.x,maxs.y,mins.z,
		maxs.x,maxs.y,mins.z,		maxs.x,mins.y,mins.z,
		maxs.x,mins.y,mins.z,		mins.x,mins.y,mins.z,
		//Top box
		mins.x,mins.y,maxs.z,		mins.x,maxs.y,maxs.z,
		mins.x,maxs.y,maxs.z,		maxs.x,maxs.y,maxs.z,
		maxs.x,maxs.y,maxs.z,		maxs.x,mins.y,maxs.z,
		maxs.x,mins.y,maxs.z,		mins.x,mins.y,maxs.z,
		//bottom to top corners
		mins.x,mins.y,mins.z,		mins.x,mins.y,maxs.z,
		mins.x,maxs.y,mins.z,		mins.x,maxs.y,maxs.z,
		maxs.x,maxs.y,mins.z,		maxs.x,maxs.y,maxs.z,
		maxs.x,mins.y,mins.z,		maxs.x,mins.y,maxs.z,
	};
	const float point_bounds[] =
	{
		mins.x-0.25f,mins.y,mins.z,		mins.x+0.25f,mins.y,mins.z,
		mins.x,mins.y-0.25f,mins.z,		mins.x,mins.y+0.25f,mins.z,
		mins.x,mins.y,mins.z-0.25f,		mins.x,mins.y,mins.z+0.25f,
	};
	int vert_count = 0;

	solid_mat->bind_material();

	if(mins.x == maxs.x && mins.y == maxs.y)
	{
		//bind axes
		solid_mat->bind_value(Shader::PARAM_VERTICES,(void*) point_bounds);
		vert_count = 6;
	}
	else
	{
		//bind cube area
		solid_mat->bind_value(Shader::PARAM_VERTICES,(void*) bounds);
		vert_count = 24;
	}

	float color[] = {1.0f,1.0f,0.0f,1.0f};
	solid_mat->bind_value(Shader::PARAM_COLOR_ADD,(void*) color);

	Mat4 trans = vp * Mat4::TRANSLATE(ofs);
	solid_mat->bind_value(Shader::PARAM_MVP_MATRIX,(void*) trans.m);
	glDrawArrays(GL_LINES, 0, vert_count);
}
//Draws active floors maneuver data
void Game::draw_floor_maneuvers(Mat4 vp)
{
	Vec3 building_org = current_building->active_floor->global_mins + Vec3(0,0,0.5f)*GRID_SIZE;
	Vec3 tile_pos;

	for(int i = 0; i < current_building->active_floor->width; i++)
	{
		for(int j = 0; j < current_building->active_floor->length; j++)
		{
			tile_pos = building_org + Vec3(i*TILE_SIZE,j*TILE_SIZE,0.0f);
			if(current_building->active_floor->tile_object[i][j]->maneuver_count)
			{
				for(int k = 0; k < current_building->active_floor->tile_object[i][j]->maneuver_count; k++)
				{
					Maneuver* man = current_building->active_floor->tile_object[i][j]->maneuvers[k];
					Vec3 ofs = tile_pos + Vec3(0,0,0.1f);
					for(int l = 0; l < man->keyframe_count; l++)
					{
						draw_keyframe(vp,man->keyframes[l],ofs);
					}
				}
			}
		}
	}
}
//Draws active floors collision voxels
void Game::draw_floor_collision_voxels(Mat4 vp)
{
	Vec3 building_org = current_building->active_floor->global_mins + Vec3(0,0,0.5f)*GRID_SIZE;
	Vec3 tile_pos;
	Vec3 voxel_pos;
	char voxel_rank;
	char voxel_shape;


/*#define CLIP_SHAPE_BOX 0
	//Solid area is the area under the line y=x
#define CLIP_SHAPE_LT_POS 1
	//Solid area is the area above the line y=x
#define CLIP_SHAPE_GT_POS 2
	//Solid area is the area under the line y=0.5-x
#define CLIP_SHAPE_LT_NEG 3
	//Solid area is the area above the line y=0.5-x
#define CLIP_SHAPE_GT_NEG 4
	//Solid area is the area under the line y=abs(x-0.25) + 0.25
#define CLIP_SHAPE_GT_ABS 5
	//Solid area is the area above the line y=-abs(x-0.25) + 0.25
#define CLIP_SHAPE_LT_ABS 6
	//Solid area is the area above the line y=x-0.15 and under the line y=x+0.15
#define CLIP_SHAPE_IN_WALL_POS 7
	//Solid area is the area above the line y=-x+0.35 and under the line y=-x+0.65
#define CLIP_SHAPE_IN_WALL_NEG 8*/

	//=========== Defining the different voxel shapes to render =============
	const float vshape_box[] =
	{
	//Top of box
	0,0,GRID_SIZE,			0,GRID_SIZE,GRID_SIZE,
	0,0,GRID_SIZE,			GRID_SIZE,0,GRID_SIZE,
	GRID_SIZE,0,GRID_SIZE,	GRID_SIZE,GRID_SIZE,GRID_SIZE,
	0,GRID_SIZE,GRID_SIZE,	GRID_SIZE,GRID_SIZE,GRID_SIZE,

	//Box x
	0,0,GRID_SIZE,			GRID_SIZE,GRID_SIZE,GRID_SIZE,
	GRID_SIZE,0,GRID_SIZE,	0,GRID_SIZE,GRID_SIZE,
	};

	const float vshape_lt_pos[] =
	{
	0,0,GRID_SIZE,			GRID_SIZE,0,GRID_SIZE,
	GRID_SIZE,0,GRID_SIZE,	GRID_SIZE,GRID_SIZE,GRID_SIZE,
	0,0,GRID_SIZE,			GRID_SIZE,GRID_SIZE,GRID_SIZE,
	};

	const float vshape_gt_pos[] =
	{
	0,0,GRID_SIZE,			0,GRID_SIZE,GRID_SIZE,
	0,GRID_SIZE,GRID_SIZE,	GRID_SIZE,GRID_SIZE,GRID_SIZE,
	0,0,GRID_SIZE,			GRID_SIZE,GRID_SIZE,GRID_SIZE,
	};
	const float vshape_lt_neg[] =
	{
	0,0,GRID_SIZE,			0,GRID_SIZE,GRID_SIZE,
	0,0,GRID_SIZE,			GRID_SIZE,0,GRID_SIZE,
	GRID_SIZE,0,GRID_SIZE,	0,GRID_SIZE,GRID_SIZE,
	};
	const float vshape_gt_neg[] =
	{
	GRID_SIZE,0,GRID_SIZE,	GRID_SIZE,GRID_SIZE,GRID_SIZE,
	0,GRID_SIZE,GRID_SIZE,	GRID_SIZE,GRID_SIZE,GRID_SIZE,
	GRID_SIZE,0,GRID_SIZE,	0,GRID_SIZE,GRID_SIZE,
	};
	const float vshape_lt_abs[] =
	{
	0,0,GRID_SIZE,			GRID_SIZE*0.5f,GRID_SIZE*0.5f,GRID_SIZE,
	GRID_SIZE,0,GRID_SIZE,		GRID_SIZE*0.5f,GRID_SIZE*0.5f,GRID_SIZE,
	0,0,GRID_SIZE,			GRID_SIZE,0,GRID_SIZE,
	};
	const float vshape_gt_abs[] =
	{
	0,GRID_SIZE,GRID_SIZE,			GRID_SIZE*0.5f,GRID_SIZE*0.5f,GRID_SIZE,
	GRID_SIZE,GRID_SIZE,GRID_SIZE,	GRID_SIZE*0.5f,GRID_SIZE*0.5f,GRID_SIZE,
	0,GRID_SIZE,GRID_SIZE,			GRID_SIZE,GRID_SIZE,GRID_SIZE,
	};

	float wall_ofs = 0.15;
	const float vshape_in_wall_pos[] =
	{
	0,0,GRID_SIZE,							wall_ofs,0,GRID_SIZE,
	0,0,GRID_SIZE,							0,wall_ofs,GRID_SIZE,
	wall_ofs,0,GRID_SIZE,					GRID_SIZE,GRID_SIZE-wall_ofs,GRID_SIZE,
	0,wall_ofs,GRID_SIZE,					GRID_SIZE-wall_ofs,GRID_SIZE,GRID_SIZE,
	GRID_SIZE,GRID_SIZE-wall_ofs,GRID_SIZE,		GRID_SIZE,GRID_SIZE,GRID_SIZE,
	GRID_SIZE-wall_ofs,GRID_SIZE,GRID_SIZE,		GRID_SIZE,GRID_SIZE,GRID_SIZE
	};
	const float vshape_in_wall_neg[] =
	{
	0,GRID_SIZE,GRID_SIZE,			wall_ofs,GRID_SIZE,GRID_SIZE,
	0,GRID_SIZE,GRID_SIZE,			0,GRID_SIZE-wall_ofs,GRID_SIZE,
	wall_ofs,GRID_SIZE,GRID_SIZE,		GRID_SIZE,wall_ofs,GRID_SIZE,
	0,GRID_SIZE-wall_ofs,GRID_SIZE,	GRID_SIZE-wall_ofs,0,GRID_SIZE,
	GRID_SIZE,wall_ofs,GRID_SIZE,		GRID_SIZE,0,GRID_SIZE,
	GRID_SIZE-wall_ofs,0,GRID_SIZE,	GRID_SIZE,0,GRID_SIZE
	};

	const GLsizei vshape_vert_counts[9] = {12,6,6,6,6,6,6,12,12};

	const float* voxel_shapes[9];
	voxel_shapes[CLIP_SHAPE_BOX] = vshape_box;
	voxel_shapes[CLIP_SHAPE_LT_POS] = vshape_lt_pos;
	voxel_shapes[CLIP_SHAPE_GT_POS] = vshape_gt_pos;
	voxel_shapes[CLIP_SHAPE_LT_NEG] = vshape_lt_neg;
	voxel_shapes[CLIP_SHAPE_GT_NEG] = vshape_gt_neg;
	voxel_shapes[CLIP_SHAPE_GT_ABS] = vshape_gt_abs;
	voxel_shapes[CLIP_SHAPE_LT_ABS] = vshape_lt_abs;
	voxel_shapes[CLIP_SHAPE_IN_WALL_POS] = vshape_in_wall_pos;
	voxel_shapes[CLIP_SHAPE_IN_WALL_NEG] = vshape_in_wall_neg;

	//=======================================================================

	solid_mat->bind_material();
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
					voxel_shape = current_building->active_floor->tile_coll_map[i][j]->get_vox_shape_at(k,l);

					solid_mat->bind_value(Shader::PARAM_VERTICES,(void*) voxel_shapes[voxel_shape]);

					if(voxel_rank == 0)
					{
						continue;
					}
					if(voxel_rank == 1)
					{
						float color[] = {0.0f,0.75f,1.0f,1.0f};
						solid_mat->bind_value(Shader::PARAM_COLOR_ADD,(void*) color);
					}
					voxel_pos = tile_pos + Vec3(k*GRID_SIZE,l*GRID_SIZE,0.0f);
					vox_trans = vp * Mat4::TRANSLATE(voxel_pos);
					solid_mat->bind_value(Shader::PARAM_MVP_MATRIX,(void*) vox_trans.m);
					glDrawArrays(GL_LINES, 0, vshape_vert_counts[voxel_shape]);
				}
			}
		}
	}
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

void Game::mnvr_movement()
{
	mnvr_y_vel += mnvr_frame->y_accel * Time::udelta_time;
	if(mnvr_y_vel <= mnvr_frame->min_y_vel)
	{
		mnvr_y_vel = mnvr_frame->min_y_vel;
	}

	player->pos.y += mnvr_y_vel * Time::udelta_time;

	//Lerping x & z player coordinates

	//Do not overshoot the goal
	float temp_y = player->pos.y > mnvr_goal_pos.y ? mnvr_goal_pos.y : player->pos.y;

	//Lerp the player x coordinate:
	player->pos.x = mnvr_var_x_slope * (temp_y - mnvr_goal_pos.y) + mnvr_goal_pos.x;

	//Lerping the player Z coordinate:
	switch(mnvr_frame->lerp_type)
	{
		default:
		case FRAME_LERP_LINEAR:
			player->pos.z = mnvr_var_a * (temp_y - mnvr_goal_pos.y) + mnvr_goal_pos.z;
			break;
		case FRAME_LERP_QUADRATIC:
			player->pos.z = (mnvr_var_a * temp_y * temp_y) + (mnvr_var_b * temp_y) + mnvr_var_c;
			break;
		case FRAME_LERP_QUAD_TO_VERT:
			player->pos.z = (mnvr_var_a * (temp_y - mnvr_goal_pos.y)*(temp_y - mnvr_goal_pos.y)) + mnvr_goal_pos.z;
			break;
		case FRAME_LERP_QUAD_FROM_VERT:
			player->pos.z = (mnvr_var_a * (temp_y - mnvr_start_pos.y)*(temp_y - mnvr_start_pos.y)) + mnvr_start_pos.z;
			break;
	}

	//Turning the player to have the right orientation
	if(mnvr_frame->orient == FRAME_ORIENT_CONSTANT)
		mnvr_goal_yaw_rot = get_keyframe_goal_yaw(mnvr_frame),player->angles.y;

	player->angles.y += (mnvr_goal_yaw_rot - player->angles.y) * mnvr_frame->orient_speed;
	//TODO tile camera for turning

	if(player->pos.y > mnvr_goal_pos.y)
	{
		reached_mnvr_keyframe();
	}
}

//Returns angle from player pos to the orientation position of the keyframe
float Game::get_keyframe_goal_yaw(Keyframe* key)
{
	float yaw;

	yaw = -atanf((mnvr_tile_ofs.x + key->orient_pos.x - player->pos.x)/(mnvr_tile_ofs.y + key->orient_pos.y - player->pos.y));
	//if the face position is behind the player, adjust results of atan
	if(player->pos.y > mnvr_tile_ofs.y + key->orient_pos.y)
		yaw += PI;

	//return angle closest to the player's yaw
	yaw = closest_angle(yaw,player->angles.y);
	return yaw;
}

void Game::reached_mnvr_keyframe ()
{
	//TODO: handle traversing logic
	//Setting up movement for keyframe:
	mnvr_frame_number = mnvr_next_frame_number;
	mnvr_next_frame_number++;
	//Are we done with this maneuver?
	if(mnvr_next_frame_number >= mnvr_current->keyframe_count)
	{
		player_state = PLAYER_STATE_RUNNING;
		mnvr_current = NULL;
		mnvr_frame = NULL;
		mnvr_next_frame = NULL;
		mnvr_frame_number = 0;
		mnvr_next_frame_number = 0;
	}
	else
	{
		mnvr_frame = mnvr_current->keyframes[mnvr_frame_number];
		mnvr_next_frame = mnvr_current->keyframes[mnvr_next_frame_number];

		//Handling animation
		switch(mnvr_frame->anim_cmd)
		{
			default:
			case FRAME_ANIM_NOOP:
				break;
			case FRAME_ANIM_PLAY:
				player_skel->play_anim(mnvr_frame->anim,mnvr_frame->anim_end_type);
				break;
			case FRAME_ANIM_PAUSE:
				player_skel->pause_anim();
				break;
			case FRAME_ANIM_RESUME:
				player_skel->resume_anim();
				break;
			case FRAME_ANIM_STOP:
				player_skel->stop_anim();
				break;
			case FRAME_ANIM_PLAY_DEFAULT:
				player_skel->play_default_anim();
				break;
		}

		//Setting up movement data for the keyframe
		mnvr_start_pos = player->pos;
		mnvr_goal_pos = cap_to_bounds(player->pos, mnvr_tile_ofs + mnvr_next_frame->mins, mnvr_tile_ofs + mnvr_next_frame->maxs);

		//Check if we are already past our goal position
		if(mnvr_start_pos.y >= mnvr_goal_pos.y)
		{
			reached_mnvr_keyframe();
			return;
		}

		if(mnvr_frame->orient)
		{
			mnvr_goal_yaw_rot = get_keyframe_goal_yaw(mnvr_frame);
		}
		else
			mnvr_goal_yaw_rot = 0.0f;

		mnvr_y_vel = mnvr_frame->y_vel;

		mnvr_var_x_slope = ((mnvr_goal_pos.x - mnvr_start_pos.x)/(mnvr_goal_pos.y - mnvr_start_pos.y));

		//Calculating the different lerp parameters needed
		switch(mnvr_frame->lerp_type)
		{
			default:
			case FRAME_LERP_LINEAR:
				mnvr_var_a = ((mnvr_goal_pos.z - mnvr_start_pos.z)/(mnvr_goal_pos.y - mnvr_start_pos.y));
				break;
			case FRAME_LERP_QUADRATIC:
				mnvr_var_a = mnvr_frame->lerp_data / (2 * mnvr_y_vel * mnvr_y_vel);
				mnvr_var_b = ((mnvr_var_a * mnvr_start_pos.y * mnvr_start_pos.y)
								- (mnvr_var_a * mnvr_goal_pos.y * mnvr_goal_pos.y)
								+ (mnvr_goal_pos.z - mnvr_start_pos.z))
							/(mnvr_goal_pos.y - mnvr_start_pos.y);
				mnvr_var_c = mnvr_start_pos.z - (mnvr_var_a * mnvr_start_pos.y * mnvr_start_pos.y) - (mnvr_var_b * mnvr_start_pos.y);
				break;
			case FRAME_LERP_QUAD_TO_VERT:
				mnvr_var_a = (mnvr_start_pos.z - mnvr_goal_pos.z)
							/ ((mnvr_start_pos.y - mnvr_goal_pos.y) * (mnvr_start_pos.y - mnvr_goal_pos.y));
				break;
			case FRAME_LERP_QUAD_FROM_VERT:
				mnvr_var_a = (mnvr_goal_pos.z - mnvr_start_pos.z)
							/ ((mnvr_goal_pos.y - mnvr_start_pos.y) * (mnvr_goal_pos.y - mnvr_start_pos.y));
				break;
		}
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
		//TODO: get voxel shape and clip type at this position.
		//Do checks to see if all points are on the same side
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

//returns true if move was successful, returns false if we collided with something and set state to DEAD
bool Game::move_player(Vec3 v)
{
	//FIXME: remove this next line and variable (just a test)
	player_colliding = false;

	//Split up movement into forward, sideways, and vertical movement
	float delta_y = v.y * Time::udelta_time;
	float delta_x = v.x * Time::udelta_time;
	float delta_z = v.z * Time::udelta_time;

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
		//FIXME: remove this next line:
		player_colliding = true;
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
		//FIXME: remove this next line:
		player_colliding = true;
	}

	//Don't do collision detection in z-axis (we let PLAYER_STATE_FALLING logic handle that)
	player->pos.z += delta_z;

	return true;
}


//Executes code if player is at specific frames in specific animations
void Game::player_anim_special_events()
{
	if(player_skel->playing_anim && player_skel->animating)
	{
		if(player_skel->current_anim == PLAYER_ANIM_RUN)//Running animation
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
}

void Game::update()
{
	//if(state.x > 0.95f && player_skel->playing_anim)
	//	player_skel->stop_anim();

	//For playing showcase hands anim
	/*static bool played_anim = false;
	if(!played_anim)
	{
		played_anim = true;
		//player_skel->play_anim(PLAYER_ANIM_SHOWCASE_HANDS,Skeleton::END_TYPE_DEFAULT_ANIM);
		player_skel->play_anim(PLAYER_ANIM_RUN,Skeleton::END_TYPE_LOOP);
	}*/


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
					move_ent->angles.x += delta_y * Time::udelta_time;
					move_ent->angles.y += delta_x * Time::udelta_time;
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
					move_ent->pos = move_ent->pos + (forward * delta_y * Time::udelta_time) + (right * delta_x * Time::udelta_time);
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
					move_ent->pos = move_ent->pos + (up * delta_y * Time::udelta_time);
					continue;
				}
			}

			//For floor generation
			if(player_state == PLAYER_STATE_CAM_FLY)
			{
				if(sx < 0.5f)
				{
					if(sy >= 0.66f && sy < 0.85f)
					{
						input_touching[i] = false;
						current_building->regenerate_floor(player->pos,buildings[NEXT_BLDG[cbldg_index]]);
						continue;
					}
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

	if(player_state == PLAYER_STATE_MANEUVERING)
	{
		camera->set_viewbob(mnvr_frame->viewbob_type);
		camera->update_viewbob();
		player_anim_special_events();
		mnvr_movement();
		return;
	}

	if(player_state == PLAYER_STATE_RUNNING)
	{
		//Get Maneuvers that require no input

		//TODO: check for traversals as well
		//Check for maneuvers that require no input or whatever input we have sent (input_swipe)
		Maneuver* man = current_building->input_to_maneuver(player->pos, INPUT_SWIPE_NONE | input_swipe);

		if(man)
		{
			player_state = PLAYER_STATE_MANEUVERING;
			mnvr_current = man;
			mnvr_tile_ofs = current_building->get_tile_ofs_at_pos(player->pos);
			mnvr_next_frame_number = 0;
			mnvr_next_frame = man->keyframes[0];
			reached_mnvr_keyframe();
			return;
		}
		else if(input_swipe)
		{
			//There was a swipe, but we are not in a maneuver area:
			if(input_swipe == INPUT_SWIPE_UP)
			{
				player_state = PLAYER_STATE_FALLING;
				player_phys_vel.z = PLAYER_JUMP_VEL;
				player_phys_vel = player_phys_vel + (Quat(player->angles.y,Vec3::UP()) * Vec3(0,PLAYER_RUN_SPEED,0));
				player_skel->play_anim(PLAYER_ANIM_RUN_JUMP,ANIM_END_TYPE_DEFAULT_ANIM);
				return;
			}
			//Get maneuvers that require input down
			if(input_swipe == INPUT_SWIPE_DOWN)
			{
				player_state = PLAYER_STATE_SLIDING;
				player_slide_speed = PLAYER_SLIDE_SPEED;
				player_substate = 0.0f;
				//In this context, subtate_time is the time that the player will slide for
				player_substate_time = t + PLAYER_SLIDE_TIME;
				player_skel->play_anim(PLAYER_ANIM_SLIDE,ANIM_END_TYPE_FREEZE);
				return;
			}
		}

		if(!player_skel->playing_anim || player_skel->current_anim != 0)
		{
			player_skel->play_anim(PLAYER_ANIM_RUN,ANIM_END_TYPE_LOOP);
		}

		player_anim_special_events();
		camera->set_viewbob(CAM_VIEWBOB_RUNNING);

		//Testing viewbob code
		static bool stepped = true;

		if(input_y[1] <= 0.1f && !stepped)
		{
			stepped = true;
			if(input_x[1] > 0.5f)
			{
				//camera->viewbob_run_footstep(-50.0f*DEG_TO_RAD,-50.0f*DEG_TO_RAD,0.0f);
			}
			else
			{
				//camera->viewbob_run_footstep(-50.0f*DEG_TO_RAD,50.0f*DEG_TO_RAD,0.0f);
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

		//Slight camera roll rotation when turning
		float tilt_angle = (player->angles.y - turn_angle) * 0.8f;
		tilt_angle = efmodf(tilt_angle + PI,TWO_PI) - PI;
		camera->tilt_angles.z = lerp_wtd_avg(camera->tilt_angles.z,tilt_angle,5.0f);
		//TODO: if not running, how do we zero this tilt angle?

		player->angles.y += (turn_angle - player->angles.y) * PLAYER_TURN_LERP_FACTOR;

		//Make the player move forward, if runs outside of building bounds, reset at building start
		Vec3 movement_vel = Quat(player->angles.y,Vec3::UP()) * Vec3(0,PLAYER_RUN_SPEED,0);

		if(!move_player(movement_vel))
			return;

		//if player is past building edge
		if(player->pos.y + PLAYER_SIZE >= current_building->global_maxs.y)
			player->pos.y = current_building->global_mins.y + PLAYER_SIZE + 0.5f;

		//Then check for more general out-of-boundsness in both x and y axes
		//player->pos = player->pos + Time::delta_time * movement_vel;
		if(current_building->is_box_out_of_bounds(player->pos,PLAYER_SIZE))//TODO: make 0.5f be the player size
		{
			player->pos = current_building->active_floor->global_pos + Vec3(0.0f,1.0f,0.0f);
		}

	}
	if(player_state == PLAYER_STATE_FALLING)
	{
		player_phys_vel.z += -9.8 * Time::udelta_time;
		if(player_phys_vel.z < -40.0f)//terminal vel
			player_phys_vel.z = -40.0f;

		Vec3 delta_pos = Time::udelta_time * player_phys_vel;

		if(player->pos.z + delta_pos.z < current_building->active_floor->altitude)
		{
			player_state = PLAYER_STATE_RUNNING;
			player->pos.z = current_building->active_floor->altitude;
			player_phys_vel = Vec3::ZERO();
			return;
		}
		player->pos = player->pos + delta_pos;
	}
	if(player_state == PLAYER_STATE_SLIDING)
	{
		//TODO: play sliding animation at start, then freeze the anim, then when we end the slide, play get back up animation
		if(player_substate_time < t)
		{
			if(player_substate == 0.0f)
			{
				player_substate = 1.0f;
				player_substate_time = t + 0.383f;//animation is 23 frames long, 23 frames @ 60 fps = 0.383 seconds
				player_skel->play_anim(PLAYER_ANIM_SLIDE_END,ANIM_END_TYPE_FREEZE);
			}
			else if(player_substate == 1.0f)
			{
				player_state = PLAYER_STATE_RUNNING;
				player_slide_speed = 0.0f;
				player_substate = 0.0f;
				player_substate_time = 0.0f;
				player_skel->play_default_anim();
			}
		}
		//In this context, subtate_time is the time that the player will slide for

		player_slide_speed += PLAYER_SLIDE_ACCEL * Time::udelta_time;
		if(player_slide_speed < PLAYER_SLIDE_MIN_SPEED)
			player_slide_speed = PLAYER_SLIDE_MIN_SPEED;

		//Player turning code:
		float turn_angle = 0.0f;
		if(input_turning)
		{
			turn_angle = -PLAYER_MAX_TURN_ANGLE * input_turn * DEG_TO_RAD;
		}
		//Slight camera roll rotation when turning
		float tilt_angle = (player->angles.y - turn_angle) * 0.8f;
		tilt_angle = efmodf(tilt_angle + PI,TWO_PI) - PI;
		camera->tilt_angles.z = lerp_wtd_avg(camera->tilt_angles.z,tilt_angle,5.0f);
		//TODO: if not running/sliding, how do we zero this tilt angle?

		player->angles.y += (turn_angle - player->angles.y) * PLAYER_TURN_LERP_FACTOR;
		player_phys_vel = (Quat(player->angles.y,Vec3::UP()) * Vec3(0,player_slide_speed,0));

		player_anim_special_events();
		camera->set_viewbob(CAM_VIEWBOB_SLIDING);
		camera->update_viewbob();

		if(!move_player(player_phys_vel))
		{
			//End slide
			//TODO: replace this with sliding death
			player_substate = 1.0f;
			player_substate_time = t + 0.383f;//animation is 23 frames long, 23 frames @ 60 fps = 0.383 seconds
			player_skel->play_anim(PLAYER_ANIM_SLIDE_END,ANIM_END_TYPE_FREEZE);
			return;
		}
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
	//Evaluating global camera position
	Vec3 global_cam_pos = camera->world_transform.get_pos();
	float cam_pos[] = {global_cam_pos.x,global_cam_pos.y,global_cam_pos.z};
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


	//buildings[0]->render(player->pos,vp);
	for(int i = 0; i < MAX_BUILDINGS; i++)
	{
		buildings[i]->render(player->pos,vp);
	}

	skybox->render(view_no_translation);
	//Have to draw transparent objects after skybox
	test_sound_source->render(vp);

	//buildings[0]->render_transparent_meshes(player->pos,vp);
	for(int i = 0; i < MAX_BUILDINGS; i++)
	{
		buildings[i]->render_transparent_meshes(player->pos,vp);
	}

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
	//draw_floor_maneuvers(vp);
	draw_player_bbox(vp);
}