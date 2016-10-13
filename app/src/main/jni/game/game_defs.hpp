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
//TODO: ...more tile type const identifiers


//Size of tiles (6 units x 6 units x 6 units)
#define TILE_SIZE 3.5f
#define WINDOW_TILE_SIZE 7.0f
#define GRID_SIZE 0.5f

#define BUILDING_MAX_WIDTH 60
#define BUILDING_MAX_LENGTH 120

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

#define INPUT_SWIPE_NONE 0
#define INPUT_SWIPE_UP 1
#define INPUT_SWIPE_DOWN 2
#define INPUT_SWIPE_LEFT 3
#define INPUT_SWIPE_RIGHT 4

//=========================== Game Logic Defs ==========================
#define MAX_BUILDINGS 5

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

#define PLAYER_JUMP_HEIGHT 0.75f
//jump vel = sqrt(PLAYER_JUMP_HEIGHT * 2.0f * 9.8f) (9.8f being acceleration of gravity)
#define PLAYER_JUMP_VEL 3.83406f

//Player Anim Defs
//NOTE: the order of these must match the order we load the animations in inside of Game.cpp
#define PLAYER_ANIM_RUN 0
#define PLAYER_ANIM_SPEED_VAULT 1
#define PLAYER_ANIM_RUN_JUMP 2
#define PLAYER_ANIM_SHOWCASE_HANDS 3



#define PARKOUR_GAME_DEFS_HPP

#endif //PARKOUR_GAME_DEFS_HPP
