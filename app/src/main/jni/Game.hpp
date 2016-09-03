//
// Created by F1 on 8/2/2016.
//

#ifndef ENGINE_GAME_HPP
#define ENGINE_GAME_HPP

#include "engine/common.hpp"
#include "entities/Camera.hpp"
#include "entities/Player.hpp"
#include "engine/graphics/UI.hpp"
#include "engine/graphics/Skybox.hpp"
#include "engine/sound/Sound_Source.hpp"
#include "engine/JNI_Interface.hpp"
#include "entities/Building.hpp"


class Game
{
public:

	Game()
	{
	}

	~Game()
	{
	}

	//Variables that engine uses
	Camera *audio_listener;
	int32_t screen_width;
	int32_t screen_height;
	float screen_ratio;// width/height

	//Access to engine-initiated JNI interface
	JNI_Interface *jnii;

	//=========================== Game Asset Variables ====================
	//-------------- Sound Files --------------
	Sound_Sample *test_pulse = NULL;

	//-------------- Shaders ------------------
	Shader *test_shader = NULL;
	Shader *skel_color_shader = NULL;
	Shader *static_color_shader = NULL;
	Shader *text_shader = NULL;
	Shader *player_skin_shader = NULL;

	//------------- Materials -----------------
	Material *mat_red = NULL;
	Material *mat_blue = NULL;
	Material *skel_color_mat= NULL;
	Material *static_color_mat = NULL;
	Material *text_mat = NULL;
	Material *player_skin_mat = NULL;

	//------------ Textures -------------------
	Texture *test_texture = NULL;
	Texture *char_set = NULL;
	Texture *tex_arm_nor = NULL;
	Texture *tex_arm_diff = NULL;
	Cube_Map *test_cube_map = NULL;

	//------------- Models --------------------
	Skel_Model *test_arms = NULL;
	Static_Model *model_prim_cube = NULL;
	Static_Model *model_prim_quad = NULL;

	Static_Model *test_model_int_empty = NULL;

	//---------- Skeletons --------------------
	Skeleton *player_skel = NULL;

	//=========================== Game Object Variables ====================
	Camera *camera = NULL;
	Player *player = NULL;
	Entity_Bone_Joint *cam_to_bone = NULL;

	Entity *test_sound_source = NULL;

	UI_Text *test_text = NULL;
	UI_Image *test_img = NULL;

	Skybox *skybox = NULL;

	Building **buildings;
	Building *current_building = NULL;

	#define MAX_BUILDINGS 5

	//======================================================================


	//========================================= Loading assets ======================================

	int load_shaders ()
	{
		test_shader = new Shader("shaders/minimal.vert","shaders/minimal.frag");
		skel_color_shader = new Shader("shaders/skeletal_color.vert","shaders/skeletal_color.frag");
		static_color_shader = new Shader("shaders/static_color.vert","shaders/static_color.frag");
		text_shader = new Shader("shaders/monochrome_transparent.vert","shaders/monochrome_transparent.frag");
		player_skin_shader = new Shader("shaders/player_skin.vert","shaders/player_skin.frag");
		return 1;
	}
	void unload_shaders ()
	{
		delete test_shader;
		delete skel_color_shader;
		delete static_color_shader;
		delete text_shader;
		delete player_skin_shader;
	}

	int load_materials()
	{
		mat_red = new Material();
		mat_blue = new Material();
		skel_color_mat = new Material();
		static_color_mat = new Material();
		text_mat = new Material();
		player_skin_mat = new Material();

		return 1;
	}
	void unload_materials()
	{
		delete mat_red;
		delete mat_blue;
		delete skel_color_mat;
		delete text_mat;
		delete player_skin_mat;
	}

	int load_textures()
	{
		test_texture = new Texture("tex.pkm",512,512);
		char_set = new Texture("char_set.pkm",2048,2048);
		tex_arm_nor = new Texture("textures/arm_nor.pkm",1024,1024);
		tex_arm_diff = new Texture("textures/arm_diff.pkm",1024,1024);
		test_cube_map = new Cube_Map("cube_maps/test_cube_map.pkm",512);
		return 1;
	}
	void unload_textures()
	{
		delete test_texture;
		delete char_set;
		delete tex_arm_nor;
		delete tex_arm_diff;
		delete test_cube_map;
	}

	int load_models()
	{
		test_arms = new Skel_Model("models/test_arms.skmf");

		model_prim_cube = new Static_Model("models/primitive_cube.stmf");
		model_prim_quad = new Static_Model("models/primitive_quad.stmf");

		test_model_int_empty = new Static_Model("models/tiles/style0/empt0.stmf");

		player_skel = new Skeleton("animations/player_skeleton.sksf");
		player_skel->load_animation("animations/run.skaf");
		player_skel->load_animation("animations/speed_vault.skaf");
		player_skel->load_animation("animations/speed_vault.skaf");
		player_skel->load_animation("animations/showcase_hands.skaf");

		skybox = new Skybox();
		return 1;
	}
	void unload_models()
	{
		delete test_arms;

		delete model_prim_cube;
		delete model_prim_quad;

		delete test_model_int_empty;

		delete player_skel;

		delete skybox;
	}

	int load_sounds()
	{
		test_pulse = new Sound_Sample("sounds/test_audio_pulse.raw");
		return 1;
	}
	void unload_sounds()
	{
		delete test_pulse;
	}

	int load_assets ()
	{
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
	void unload_assets ()
	{
		unload_sounds();
		unload_models();
		unload_materials();
		unload_shaders();
		unload_textures();
	}
	//=================================================================================================
	//Initialize GL aspects of all assets
	int init_gl()
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
		return 1;
	}

	void term_gl()
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

		//Terminating all loaded textures
		test_cube_map->term_gl();
		tex_arm_nor->term_gl();
		tex_arm_diff->term_gl();
		char_set->term_gl();
		test_texture->term_gl();
	}

	//Ran on first frame
	//This is where we set up our game objects and their relationships
	void start();
	//Ran on last frame
	//This is where we destroy our game objects
	void finish();
	//Input static identifiers
	const static int INPUT_EVENT_ON_TOUCH_DOWN = 1;
	const static int INPUT_EVENT_ON_TOUCH_MOVE = 2;
	const static int INPUT_EVENT_ON_TOUCH_RELEASE = 3;

	//Temp test input variables
	bool input_touching = false;
	float input_x = 0.0f;
	float input_y = 0.0f;

	float input_start_x = 0.0f;
	float input_start_y = 0.0f;

	bool input_turning = false;
	bool input_sent_command = false;

	int input_swipe;
	static const int INPUT_SWIPE_UP = 1;
	static const int INPUT_SWIPE_DOWN = 2;
	static const int INPUT_SWIPE_LEFT = 3;
	static const int INPUT_SWIPE_RIGHT = 4;

	float input_turn;

	//Defined as the percentage of the screen width the finger must be dragged before we register a swipe
	float input_sensitivity = 0.0625f;


	void handle_input(float x, float y, int event)
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


	float player_runspeed = 6.0f;

	//From center to edge of the player bbox's square base
	float player_bbox_half_size = 0.5f;

	int player_state = 0;
	float player_substate = 0.0f;

	static const int PLAYER_STATE_MENU = 0;
	static const int PLAYER_STATE_RUNNING = 1;
	static const int PLAYER_STATE_FALLING = 2;
	static const int PLAYER_STATE_SLIDING = 3;
	static const int PLAYER_STATE_MANEUVERING = 4;
	static const int PLAYER_STATE_TRAVERSING = 5;


	//Updates the game state / logic
	void update();

	//Draws the scene
	void render();

};

#endif //ENGINE_GAME_HPP
