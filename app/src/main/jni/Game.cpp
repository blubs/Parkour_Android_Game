//
// Created by F1 on 8/2/2016.
//

#include "Game.hpp"


int Game::load_shaders ()
{
	test_shader = new Shader("shaders/minimal.vert","shaders/minimal.frag");
	skel_color_shader = new Shader("shaders/skeletal_color.vert","shaders/skeletal_color.frag");
	static_color_shader = new Shader("shaders/static_color.vert","shaders/static_color.frag");
	text_shader = new Shader("shaders/monochrome_transparent.vert","shaders/monochrome_transparent.frag");
	player_skin_shader = new Shader("shaders/player_skin.vert","shaders/player_skin.frag");
	return 1;
}
void Game::unload_shaders ()
{
	delete test_shader;
	delete skel_color_shader;
	delete static_color_shader;
	delete text_shader;
	delete player_skin_shader;
}

int Game::load_materials()
{
	mat_red = new Material();
	mat_blue = new Material();
	skel_color_mat = new Material();
	static_color_mat = new Material();
	text_mat = new Material();
	player_skin_mat = new Material();

	return 1;
}
void Game::unload_materials()
{
	delete mat_red;
	delete mat_blue;
	delete skel_color_mat;
	delete text_mat;
	delete player_skin_mat;
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
	//player_skel->load_animation("animations/speed_vault.skaf");
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
	//Initializing shaders
	GLuint param_types[] =
	{
	Shader::PARAM_VERTICES,
	Shader::PARAM_VERT_COLORS,
	Shader::PARAM_VERT_UV1,
	Shader::PARAM_TEXTURE_DIFFUSE,
	Shader::PARAM_MVP_MATRIX,
	Shader::PARAM_TEST_FIELD
	};
	const char *param_names[] =
	{
	"vert_pos",
	"fill_color",
	"src_tex_coord",
	"tex",
	"mvp",
	"test_color_param"
	};
	test_shader->init_gl(param_types, param_names,6);

	//======================================= Initializing the UI text shader =================================
	GLuint text_param_types[] =
	{
	Shader::PARAM_VERTICES,
	Shader::PARAM_VERT_UV1,
	Shader::PARAM_TEXTURE_DIFFUSE,
	Shader::PARAM_MVP_MATRIX,
	Shader::PARAM_COLOR_MULT,
	Shader::PARAM_COLOR_ADD
	};
	const char *text_param_names[] =
	{
	"vert_pos",
	"src_tex_coord",
	"tex",
	"mvp",
	"mult_color",
	"add_color"
	};
	text_shader->init_gl(text_param_types, text_param_names,6);

	//========================================= Initializing the skeletal mesh shader ================================
	GLuint skel_mesh_params[] =
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
	const char *skel_mesh_param_names[] =
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
	skel_color_shader->init_gl(skel_mesh_params, skel_mesh_param_names, 9);

	//========================================= Initializing Player Skin Skeletal Shader =============================
	GLuint player_skin_params[] =
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
	const char *player_skin_param_names[] =
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
	player_skin_shader->init_gl(player_skin_params,player_skin_param_names,13);

	//=========================================== Initializing Static Mesh Color Shader =====================
	GLuint static_mesh_params[] =
	{
	Shader::PARAM_VERTICES,
	Shader::PARAM_VERT_UV1,
	Shader::PARAM_VERT_UV2,
	Shader::PARAM_VERT_NORMALS,
	Shader::PARAM_MVP_MATRIX,
	Shader::PARAM_M_IT_MATRIX,
	Shader::PARAM_COLOR_MULT
	};
	const char *static_mesh_param_names[] =
	{
	"vert_pos",
	"vert_uv_1",
	"vert_uv_2",
	"vert_nor",
	"mvp",
	"m_IT",
	"color"
	};
	static_color_shader->init_gl(static_mesh_params, static_mesh_param_names, 7);

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

void Game::handle_input(float x, float y, int event)
{
	y = 1.0f - y;
	//TODO: handle gamestates such as menu / pause menu
	if(event == INPUT_EVENT_ON_TOUCH_DOWN)
	{
		input_turning = false;
		input_sent_command = false;
		input_touching = true;
		input_start_x = x;
		input_start_y = y;
	}
		//else if(event == INPUT_EVENT_ON_TOUCH_MOVE)
		//{
		//
		//}
	else if(event == INPUT_EVENT_ON_TOUCH_RELEASE)
		{
			input_turning = false;
			input_sent_command = false;
			input_touching = false;
			input_start_x = 0.0f;
			input_start_y = 0.0f;
		}

	switch(event)
	{
		case INPUT_EVENT_ON_TOUCH_DOWN:
		case INPUT_EVENT_ON_TOUCH_MOVE:
		case INPUT_EVENT_ON_TOUCH_RELEASE:
			input_x = x;
			input_y = y;
			break;
		default:
			break;
	}

	input_turn = 0;
	input_swipe = 0;

	if(input_sent_command)
		return;

	float delta_x = input_x - input_start_x;
	float delta_y = input_y - input_start_y;
	float delta_x_abs = fabsf(delta_x);
	float delta_y_abs = fabsf(delta_y);

	//Check if we are swiping horizontally or already turning
	if(input_turning || ((delta_x_abs > delta_y_abs) && (delta_x_abs > input_sensitivity)))
	{
		//if input_sensitivity is 1/16, the 16.0f and it annihilate each other
		//Making us only have to swipe 1/3rd of the screen width to go through the full range of motion
		input_turn = 3.0f * 16.0f * delta_x * input_sensitivity;
		input_turn = fmaxf(0.0f,fminf(1.0f,input_turn));

		input_turning = true;
		return;
	}

	//Check if we are swiping vertically
	if(delta_y_abs > delta_x_abs)
	{
		if(delta_y_abs > input_sensitivity*screen_ratio)
		{
			input_swipe = INPUT_SWIPE_UP;
			input_sent_command = true;
		}
		if(delta_y_abs < -input_sensitivity*screen_ratio)
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
	camera->set_persp_view(90.0f * DEG_TO_RAD, screen_width,screen_height, 0.01f, 1000.0f);
	camera->set_ortho_view(screen_width,screen_height,0.0001f,1.0f);

	//Start of game logic code
	buildings = new Building*[MAX_BUILDINGS];

	for(int i = 0; i < MAX_BUILDINGS; i++)
	{
		buildings[i] = new Building();
	}

	buildings[0]->generate();

	current_building = buildings[0];

	player->pos.y = 1;
	player_state = PLAYER_STATE_RUNNING;
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

void Game::update()
{
	//if(state.x > 0.95f && player_skel->playing_anim)
	//	player_skel->stop_anim();

	//For test playing vault animation
	static bool played_anim = false;
	if(!played_anim)
	{
		played_anim = true;
		//player_skel->play_anim(2,Skeleton::END_TYPE_DEFAULT_ANIM);
		player_skel->play_anim(2,Skeleton::END_TYPE_LOOP);
	}
	//if(state.x < 0.10f)
	//{
	//	if( player_skel->current_anim != 2 && !played_anim)
	//	{
	//		played_anim = true;
	//		player_skel->play_anim(2,Skeleton::END_TYPE_DEFAULT_ANIM);
	//	}
	//}
	//else
	//{
	//	played_anim = false;
	//}

	//====Test show/hide ad calls====
	static bool ad_visible = false;
	if(input_x < 0.10f && ad_visible)
	{
		jnii->hide_ad();
		ad_visible = false;
	}
	else if(input_x > 0.90f && !ad_visible)
		{
			jnii->show_ad();
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

	//TODO: handle input here
	//TODO: check for maneuvers and traversals

	if(player_state == PLAYER_STATE_RUNNING)
	{
		camera->set_viewbob(Camera::VIEWBOB_RUNNING);

		//Testing viewbob code
		static bool stepped = true;

		if(input_y <= 0.1f && !stepped)
		{
			stepped = true;
			if(input_x > 0.5f)
			{
				camera->viewbob_run_footstep(-50.0f*DEG_TO_RAD,-50.0f*DEG_TO_RAD,0.0f);
			}
			else
			{
				camera->viewbob_run_footstep(-50.0f*DEG_TO_RAD,50.0f*DEG_TO_RAD,0.0f);
			}
		}
		else if(input_y > 0.1f)
				stepped = false;
		//========================= end test viewbob code

		camera->update_viewbob();

		if(player->pos.z > current_building->active_floor->altitude)
		{
			player_state = PLAYER_STATE_FALLING;
		}


		//Make the player move forward, if runs outside of building bounds, reset at building start
		Vec3 movement_vel = Vec3(0,player_runspeed,0);

		player->pos = player->pos + Time::delta_time * movement_vel;

		if(current_building->is_box_out_of_bounds(player->pos,0.5f))//TODO: make 0.5f be the player size
		{
			player->pos = current_building->active_floor->global_pos + Vec3(0.0f,1.0f,0.0f);
		}

		//TODO: run logic
	}
	if(player_state == PLAYER_STATE_FALLING)
	{
		//TODO: slide logic
		//TODO: add physics velocity and acceleration
		Vec3 movement_vel;
		//physics_vel = physics_vel + Time::delta_time * gravity;
		//movement_vel = physics_vel
		Vec3 delta_pos = Time::delta_time * movement_vel;

		if(player->pos.z + delta_pos.z < current_building->active_floor->altitude)
		{
			player_state = PLAYER_STATE_RUNNING;
			player->pos.y = current_building->active_floor->altitude;
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

	skybox->render(view_no_translation);

	//Have to draw transparent objects after skybox
	test_sound_source->render(vp);

	buildings[0]->render(vp);


	//Test UI image
	//test_img->render(camera->ortho_proj_m);

	//Test UI Text
	//char time_str[20];
	//snprintf(time_str,20,"t=%f",t);
	//test_text->set_text(time_str);
	//test_text->render(camera->ortho_proj_m);
}