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
	float y_vel;//y speed for keyframe
	float dy_vel;//y axis acceleration (for speeding up or slowing down)
	float min_y_vel;//minimum y axis speed

	//z-axis interpolation types
	int lerp_type;//interpolation used for z-axis (spherical, linear, quadratic, inverse quadratic)
	float lerp_data;

	//Turn the player towards a direction
	int orient;
	Vec3 orient_pos;//x & y coordinates of point that player faces as we head towards keyframe

	//Animation to play starting at this keyframe
	int anim;

	//Special keyframe data (for letting the player know to do special things)
	int spec_flag;

	void set_info(Vec3 _mins, Vec3 _maxs, float _y_vel, float _dy_vel, float _min_y_vel, int _lerp_type, float _lerp_data, int _orient, Vec3 _orient_pos, int _anim, int _spec_flag)
	{
		this->mins = _mins;
		this->maxs = _maxs;
		this->y_vel = _y_vel;
		this->dy_vel = _dy_vel;
		this->min_y_vel = _min_y_vel;
		this->lerp_type = _lerp_type;
		this->lerp_data = _lerp_data;
		this->orient = _orient;
		this->orient_pos = _orient_pos;
		this->anim = _anim;
		this->spec_flag = _spec_flag;
	}
};

class Maneuver
{
public:
	Keyframe keyframes[];
	int keyframe_count = 0;
	int input_required = 0;

	Maneuver( int frame_count)
	{
		keyframe_count = frame_count;
		keyframes = new Keyframe[frame_count];
	}

	~Maneuver()
	{
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
