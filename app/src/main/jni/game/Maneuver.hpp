//
// Created by F1 on 9/19/2016.
//

#ifndef PARKOUR_MANEUVER_HPP
#define PARKOUR_MANEUVER_HPP

#include "../engine/common.hpp"

class Keyframe
{
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
	int face_something;
	Vec3 face_position;//x & y coordinates of point that player faces as we head towards keyframe

	//Animation to play starting at this keyframe
	int animation;

	//Special keyframe data (for letting the player know to do special things)
	int special_flag;

	void set_info(Vec3 _mins, Vec3 _maxs, Vec3 )
	{

	}
};

class Maneuver
{
public:
	Keyframe keyframes[];
};

class Traversal : Maneuver
{
public:
};

#endif //PARKOUR_MANEUVER_HPP
