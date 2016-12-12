//
// Created by F1 on 10/12/2016.
//

#ifndef PARKOUR_GAME_DEFS_HPP

#include "../engine/engine_defs.hpp"

//========================= Tile Defs =====================================

//Total count of tile types
#define TILE_TYPES 2

#define TILE_TYPE_EMPT 0
#define TILE_TYPE_SOLD 1
#define TILE_TYPE_WALL 2
//FIXME: this next one is temp
#define TILE_TYPE_OBST 3
//TODO: ...more tile type const identifiers

//Collision map Voxel Clip Types
#define CLIP_EMPTY 0
#define CLIP_SOLID 1
//#define CLIP_DOORWAY 2
//...etc

//Wall types: to be read as such:
//the wall always touches the center of the 3x3 tile
	//x is -x axis
	//X is +x axis
	//y is -y axis
	//Y is +y axis
	//o means the wall does not touch that axis
		//Example: xXoo		means the wall extends from -x to +x, through the center
		//Example: ooyY		means the wall extends from -y to +y, through the center
		//Example: xXyY		means the wall forms a '+' through the center
//Integral wall types that make up the rest

#define WALL_TYPE_oooo 0//this wall type should be neither referenced nor accessed (it's an empty floor with no walls), it is here to maintain the binary assignment of walls
#define WALL_TYPE_xooo 1
#define WALL_TYPE_oXoo 2
#define WALL_TYPE_xXoo ( WALL_TYPE_xooo | 	WALL_TYPE_oXoo 								)//3
#define WALL_TYPE_ooyo 4
#define WALL_TYPE_xoyo ( WALL_TYPE_xooo | 					WALL_TYPE_ooyo 				)//5
#define WALL_TYPE_oXyo ( 				WALL_TYPE_oXoo | 	WALL_TYPE_ooyo 				)//6
#define WALL_TYPE_xXyo ( WALL_TYPE_xooo | 	WALL_TYPE_oXoo | 	WALL_TYPE_ooyo 				)//7
#define WALL_TYPE_oooY 8
#define WALL_TYPE_xooY ( WALL_TYPE_xooo | 									WALL_TYPE_oooY )//9
#define WALL_TYPE_oXoY ( 				WALL_TYPE_oXoo | 					WALL_TYPE_oooY )//10
#define WALL_TYPE_xXoY ( WALL_TYPE_xooo | 	WALL_TYPE_oXoo | 					WALL_TYPE_oooY )//11
#define WALL_TYPE_ooyY ( 							 	WALL_TYPE_ooyo | 	WALL_TYPE_oooY )//12
#define WALL_TYPE_xoyY ( WALL_TYPE_xooo | 					WALL_TYPE_ooyo | 	WALL_TYPE_oooY )//13
#define WALL_TYPE_oXyY ( 				WALL_TYPE_oXoo | 	WALL_TYPE_ooyo | 	WALL_TYPE_oooY )//14
#define WALL_TYPE_xXyY ( WALL_TYPE_xooo | 	WALL_TYPE_oXoo | 	WALL_TYPE_ooyo | 	WALL_TYPE_oooY )//15

#define WALL_TYPE_COUNT 16

//We define the above such that we can construct types out of other types. while maintaining the wall's spatial logic
// i.e. adding a left wall segment (xooo) and a right wall segment (oXoo) , yields a full horizontal wall (xXoo)
	// xooo | oXoo = xXoo

//Size of tiles (6 units x 6 units x 6 units)
#define TILE_SIZE 3.5f
#define WINDOW_TILE_SIZE 7.0f
#define GRID_SIZE 0.5f

#define BUILDING_MAX_WIDTH 60
#define BUILDING_MAX_LENGTH 120
#define BUILDING_MAX_HEIGHT 40
#define BUILDING_MAX_EXTERIOR_MODELS 200
#define BUILDING_MAX_INTERIOR_MODELS 40
#define BUILDING_WINDOW_MAX_TILE_MATRIX 5

//2 voxels per meter, 3.5m x 3.5m tile = 7v x 7v voxel map
#define TILE_VOXEL_DIMS 7
//Total number of voxels per tile (7x7)
#define TILE_VOXELS 49


//====================== Maneuver Keyframe Defs ==========================
//Lerp types
#define FRAME_LERP_LINEAR 0
#define FRAME_LERP_QUADRATIC 1
#define FRAME_LERP_QUAD_FROM_VERT 2
#define FRAME_LERP_QUAD_TO_VERT 3

//Player orientation types
#define FRAME_ORIENT_NONE 0
#define FRAME_ORIENT_ONCE 1
#define FRAME_ORIENT_CONSTANT 2

//Camera viewbob Identifiers
#define CAM_VIEWBOB_NONE 0
#define CAM_VIEWBOB_RUNNING 1
#define CAM_VIEWBOB_SLIDING 2

//Frame animation commands
#define FRAME_ANIM_NOOP 0
#define FRAME_ANIM_PLAY 1
#define FRAME_ANIM_PAUSE 2
#define FRAME_ANIM_RESUME 3
#define FRAME_ANIM_STOP 4
#define FRAME_ANIM_PLAY_DEFAULT 5

//Special flags
#define FRAME_SPECFLAG_NONE 0
//TODO: actual special flags...


//============================ Input Defs ==============================

//Defined as the percentage of the screen width the finger must be dragged before we register a swipe
#define INPUT_SENSITIVITY 0.0625f

//Input identifiers
#define INPUT_EVENT_ON_TOUCH_DOWN 1
#define INPUT_EVENT_ON_TOUCH_MOVE 2
#define INPUT_EVENT_ON_TOUCH_RELEASE 3

#define INPUT_SWIPE_NONE 1
#define INPUT_SWIPE_UP 2
#define INPUT_SWIPE_DOWN 4
#define INPUT_SWIPE_LEFT 8
#define INPUT_SWIPE_RIGHT 16

//Keyboard input defs
#define INPUT_KEY_BACK 1
#define INPUT_KEY_KEYBOARD 2

//Array used for filtering out unwanted characters from keyboard input
//Here we filter out all control characters, except for ' ','\b', and '\n'. (keeps all symbolic & alphanumeric)
extern char INPUT_CHAR_FILTER[128];
//Definition is in game_defs.cpp

//=========================== Game Logic Defs ==========================
#define MAX_BUILDINGS 3

//Player States
#define PLAYER_STATE_MENU 0
#define PLAYER_STATE_RUNNING 1
#define PLAYER_STATE_FALLING 2
#define PLAYER_STATE_SLIDING 3
#define PLAYER_STATE_MANEUVERING 4
#define PLAYER_STATE_TRAVERSING 5

#define PLAYER_STATE_NOCLIP 6
#define PLAYER_STATE_CAM_FLY 7

//Player Data
#define PLAYER_SIZE 0.5f
#define PLAYER_MAX_TURN_ANGLE 60.0f
#define PLAYER_RUN_SPEED 6.0f

#define PLAYER_TURN_LERP_FACTOR 0.5f

#define PLAYER_SLIDE_SPEED 6.0f
#define PLAYER_SLIDE_ACCEL -3.0f
#define PLAYER_SLIDE_MIN_SPEED 0.5f
//Slide time in seconds
#define PLAYER_SLIDE_TIME 1.1f


#define PLAYER_JUMP_HEIGHT 0.75f
//jump vel = sqrt(PLAYER_JUMP_HEIGHT * 2.0f * 9.8f) (9.8f being acceleration of gravity)
#define PLAYER_JUMP_VEL 3.83406f

//Player Anim Defs
//NOTE: the order of these must match the order we load the animations in inside of Game.cpp
#define PLAYER_ANIM_RUN 0
#define PLAYER_ANIM_SPEED_VAULT 1
#define PLAYER_ANIM_RUN_JUMP 2
#define PLAYER_ANIM_SLIDE 3
#define PLAYER_ANIM_SLIDE_END 4
#define PLAYER_ANIM_SHOWCASE_HANDS 5



#define PARKOUR_GAME_DEFS_HPP

#endif //PARKOUR_GAME_DEFS_HPP
