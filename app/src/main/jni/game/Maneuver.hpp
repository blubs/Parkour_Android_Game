//
// Created by F1 on 9/19/2016.
//

#ifndef PARKOUR_MANEUVER_HPP
#define PARKOUR_MANEUVER_HPP

#include "../engine/common.hpp"

class Keyframe
{
public:
	//Boundary for executing keyframe
	Vec3 mins;
	Vec3 maxs;

	//Y velocity for the frame
	float y_vel = 0;//y speed for keyframe
	float y_accel = 0;//y axis acceleration (for speeding up or slowing down)
	float min_y_vel = 0;//minimum y axis speed

	//z-axis interpolation types
	int lerp_type = 0;//interpolation used for z-axis (spherical, linear, quadratic, inverse quadratic)
	float lerp_data = 0;

	const static int LERP_LINEAR = 0;
	const static int LERP_QUADRATIC = 1;
	const static int LERP_QUAD_FROM_VERT = 2;
	const static int LERP_QUAD_TO_VERT = 3;


	//Turn the player towards a direction
	int orient = 0;
	Vec3 orient_pos;//x & y coordinates of point that player faces as we head towards keyframe

	const static int ORIENT_NONE = 0;
	const static int ORIENT_ONCE = 1;
	const static int ORIENT_CONSTANT = 2;

	//Animation to play starting at this keyframe
	int anim = 0;

	//Special keyframe data (for letting the player know to do special things)
	int spec_flag = 0;


	int input_required = 0;

	const static int INPUT_NONE = 0;
	const static int INPUT_UP = 1;
	const static int INPUT_DOWN = 3;

	void set_info(Vec3 _mins, Vec3 _maxs, float _y_vel, float _y_accel, float _min_y_vel, int _lerp_type, float _lerp_data, int _orient, Vec3 _orient_pos, int _anim, int _spec_flag)
	{
		mins = _mins;
		maxs = _maxs;
		y_vel = _y_vel;
		y_accel = _y_accel;
		min_y_vel = _min_y_vel;
		lerp_type = _lerp_type;
		lerp_data = _lerp_data;
		orient = _orient;
		orient_pos = _orient_pos;
		anim = _anim;
		spec_flag = _spec_flag;
	}
	void set_bounds(Vec3 _mins, Vec3 _maxs)
	{
		mins = _mins;
		maxs = _maxs;
	}
	void set_speed(float _y_vel, float _y_accel, float _min_y_vel)
	{
		y_vel = _y_vel;
		y_accel = _y_accel;
		min_y_vel = _min_y_vel;
	}
	void set_lerp(int _lerp_type, float _lerp_data)
	{
		lerp_type = _lerp_type;
		lerp_data = _lerp_data;
	}

	void set_orient(int _orient, Vec3 _orient_pos)
	{
		orient = _orient;
		orient_pos = _orient_pos;
	}

	void set_anim(int _anim)
	{
		anim = _anim;
	}

	void set_specflag(int _spec_flag)
	{
		spec_flag = _spec_flag;
	}

};

class Maneuver
{
public:
	Keyframe** keyframes;
	int keyframe_count = 0;
	int input_required = 0;

	Maneuver( int frame_count)
	{
		keyframe_count = frame_count;
		keyframes = new Keyframe*[frame_count];
		for(int i = 0; i < frame_count; i++)
		{
			keyframes[i] = new Keyframe();
		}
	}

	~Maneuver()
	{
		for(int i = 0; i < keyframe_count; i++)
		{
			delete keyframes[i];
		}
		delete[] keyframes;
	}

};

class Traversal : Maneuver
{
public:
	//TODO: what misc data is required for traversal?
	Traversal(int frame_count) : Maneuver(frame_count)
	{

	}
};

#endif //PARKOUR_MANEUVER_HPP
