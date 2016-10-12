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
#include "game/Global_Tiles.hpp"


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
	Shader *solid_shader = NULL;

	//------------- Materials -----------------
	Material *mat_red = NULL;
	Material *mat_blue = NULL;
	Material *skel_color_mat= NULL;
	Material *static_color_mat = NULL;
	Material *text_mat = NULL;
	Material *player_skin_mat = NULL;
	Material *solid_mat = NULL;

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

	int load_shaders();
	void unload_shaders();

	int load_materials();
	void unload_materials();

	int load_textures();
	void unload_textures();

	int load_models();
	void unload_models();

	int load_sounds();
	void unload_sounds();

	int load_assets();
	void unload_assets();
	//=================================================================================================
	//Initialize GL aspects of all assets
	int init_gl();

	void term_gl();

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

	//input variables
	#define MAX_INPUT_TOUCHES 10
	bool input_touching[10] = {false,false,false,false,false,false,false,false,false,false};
	float input_x[10] = {0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
	float input_y[10] = {0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
	float input_start_x[10] = {0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
	float input_start_y[10] = {0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};

	bool input_turning = false;
	bool input_sent_command = false;

	int input_swipe;
	static const int INPUT_SWIPE_NONE = 0;
	static const int INPUT_SWIPE_UP = 1;
	static const int INPUT_SWIPE_DOWN = 2;
	static const int INPUT_SWIPE_LEFT = 3;
	static const int INPUT_SWIPE_RIGHT = 4;

	float input_turn;

	//Defined as the percentage of the screen width the finger must be dragged before we register a swipe
	float input_sensitivity = 0.0625f;


	void handle_input(float x, float y, int event,int pointer_id);


	float player_runspeed = 6.0f;

	Vec3 player_phys_vel;

	//From center to edge of the player bbox's square base
	float player_bbox_half_size = 0.5f;

	int player_state = 0;
	float player_substate = 0.0f;

	//FIXME: remove this
	//===================
	int viewbob_menu_state = 0;
	float viewbob_pitch;
	float viewbob_yaw;
	float viewbob_roll;
	//===================

	static const int PLAYER_STATE_MENU = 0;
	static const int PLAYER_STATE_RUNNING = 1;
	static const int PLAYER_STATE_FALLING = 2;
	static const int PLAYER_STATE_SLIDING = 3;
	static const int PLAYER_STATE_MANEUVERING = 4;
	static const int PLAYER_STATE_TRAVERSING = 5;

	static const int PLAYER_STATE_NOCLIP = 6;
	static const int PLAYER_STATE_CAM_FLY = 7;

	#define PLAYER_SIZE 0.5f
	#define PLAYER_MAX_TURN_ANGLE 60.0f
	float player_bbox_tri_slope = 0.0f;
	float player_bbox_tri_height = 0.0f;


	//Updates the game state / logic
	void update();

	//Draws the scene
	void render();

	//==== Game logic specific methods =====
	//Handles player collision detection and player movement
	bool move_player(Vec3 v);
	//Handles player bbox hull collision with building->floor->tile voxels
	char clip_player_bbox(Vec3 p);

	//Executes code if player is at specific frames in specific animations
	void player_anim_special_events();

	//Draws player bounding box
	void draw_player_bbox(Mat4 vp);
	//Draws active floors collision voxels
	void draw_floor_collision_voxels(Mat4 vp);
	//Draws active floors maneuver data
	//TODO: implement this method
	void draw_floor_maneuvers(Mat4 vp);

	//====== Maneuver variables ======
	Maneuver* mnvr_current;
	Traversal* trav_current;
	Keyframe* mnvr_frame;
	int mnvr_frame_number;
	Keyframe* mnvr_next_frame;
	int mnvr_next_frame_number;
	//Global position of the tile this maneuver is owned by
	Vec3 mnvr_tile_ofs;
	//Global goal position we're moving to
	Vec3 mnvr_goal_pos;
	//Global start position we're moving to
	Vec3 mnvr_start_pos;
	//Yaw Rotation Orientation of player
	float mnvr_goal_yaw_rot;
	//current y-axis speed of keyframe
	float mnvr_y_vel;
	//Returns the pos if in mins & maxs, otherwise caps to lie within the mins & maxs
	Vec3 cap_to_bounds(Vec3 pos, Vec3 mins, Vec3 maxs);
	//Variables used for quadratic movement
	float mnvr_var_a;
	float mnvr_var_b;
	float mnvr_var_c;

	//Slope of the line that makes up the player path in the x-y axis
	float mnvr_var_x_slope;

	void mnvr_movement();
	//Sets up the movement from the frame we're at, to the next frame in the sequence (or last frame)
	void reached_mnvr_keyframe();
	//Returns angle from player pos to the orientation position of the keyframe
	float get_keyframe_goal_yaw(Keyframe* key);

};

#endif //ENGINE_GAME_HPP
